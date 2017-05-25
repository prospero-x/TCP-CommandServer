#include <boost/interprocess/detail/config_begin.hpp>
//[doc_message_queueA
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ucirc_server.h"
#include <unistd.h>
#include <string.h>
#include <boost/asio.hpp>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <utility>
#include "client.h"
#include "messages.h"
#include "handler.h"
#include "crontab.h"


using namespace boost::interprocess;

struct ThreadArgs
{
    ucirc_server_t *server;
	client_t *client;
};

ucirc_server_t *create_server()
{
    ucirc_server_t* server = (ucirc_server_t*)malloc(sizeof(ucirc_server_t));
    server->interval = get_interval_from_file();
    server->night = check_crontab();
    update_log_indicator_file(server->night);
    return server;
}

/* A hacky way to do Inter-processs commuication. 
 * The log scripts must know to only copy during 
 * the night. Therefore this file will be called 
 * every time the night bit is updated. */
void update_log_indicator_file(int night)
{
    char command[LOG_INDICATOR_COMMAND_LENGTH];
    memset(command, 0, LOG_INDICATOR_COMMAND_LENGTH);
    snprintf(command, LOG_INDICATOR_COMMAND_LENGTH, "echo %d > %s", 
        night, LOG_INDICATOR_FILE);
    system(command);
    return;
}

void set_interval_file(int interval)
{
    char command[INTERVAL_FILE_COMMAND_LENGTH];
    memset(command, 0, INTERVAL_FILE_COMMAND_LENGTH);
    snprintf(command, INTERVAL_FILE_COMMAND_LENGTH, "echo %d > %s", 
        interval, INTERVAL_FILE);
    system(command);
    return;
}

void send_singleton()
{
    system(SINGLETON_PROGRAM);
    return;
}

int get_interval_from_file()
{
    char num[5];
    memset(num, 0, 5);
    FILE *fp = fopen(INTERVAL_FILE, "r");
    fread(num, 1, 2, fp);
    fclose(fp);
    return atoi(num);
}

char* debug_replace_token(char* string)
{
    int end = strlen(string);
    int ret_end = end*2;
    char * ret_str = (char *)malloc(ret_end);
    while(--end >= 0)
    {
    
        if (string[end] == '\n')
        {
            ret_str[--ret_end] = 'n';
            ret_str[--ret_end] = '\\';
        }
        else if (string[end] == '\r')
        {
            ret_str[--ret_end] = 'r';
            ret_str[--ret_end] = '\\';
        }
        else
            ret_str[--ret_end] = string[end];
    } 
    ret_str += ret_end; 
    return ret_str;
}   


void *client_session(void *arg)
{
    struct ThreadArgs *thread_args = (struct ThreadArgs*)arg;
    ucirc_server_t *server = thread_args->server;
	client_t *client = thread_args->client;
	int clientSocket = client->clientSocket;
	struct sockaddr_in *client_addr_info = client->socket_info;



	char buffer[BUFFER_SIZE];
                printf("Client thread: waiting to receive a message\n");
		int num_bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (num_bytes == -1)
		{
			perror("recv failed");
			close(clientSocket);
		}
		else
		{
			buffer[num_bytes] = '\0';
                        printf("Just received the command: `%s`\n", debug_replace_token(buffer));
			char * reply = ucirc_process_buffer(server, buffer);
                        printf("Sending back the command: `%s`\n\n\n", debug_replace_token(reply));
            if (send(clientSocket, reply, strlen(reply),0) < 0)
            {
                printf("Send() back to client failed.");
            }
            free(reply);
	}
    close(clientSocket);
    free(client_addr_info);
    free(client);

    pthread_exit(NULL);
    return NULL;
}


int main (int argc, char** argv)
{       
    int serverSocket;
    int yes = 1;
    struct addrinfo hints, *res, *p;
    socklen_t sinSize = sizeof(struct sockaddr_storage);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT, &hints, &res) != 0)
    {
    	perror ("getaddrinfo() failed");
    	return -2;
    }
    for(p = res;p != NULL; p = p->ai_next) 
	{
        if ((serverSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("Could not open socket");
            continue;
        }

        if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("Socket setsockopt() failed");
            close(serverSocket);
            continue;
        }

        if (bind(serverSocket, p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("Socket bind() failed");
            close(serverSocket);
            continue;
        }

        if (listen(serverSocket, 5) == -1)
        {
            perror("Socket listen() failed");
            close(serverSocket);
            continue;
        }
   		break;
	}
	freeaddrinfo(res);
	if (p == NULL)
	{
	    fprintf(stderr, "Could not find a socket to bind to.\n");
	    pthread_exit(NULL);
	}
    ucirc_server_t *server = create_server();
	while(1)
	{	struct sockaddr_in *addr = (struct sockaddr_in*)p->ai_addr;
		int clientSocket;
		struct sockaddr_in *client_addr_info = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

		clientSocket = accept(serverSocket, 
						(struct sockaddr *) client_addr_info,
						& sinSize);
		if (clientSocket == -1)
		{
			perror("Client Socket accept() failed");
			continue;
		}
                system("date");
                printf("Now connected with %s\n", inet_ntoa(client_addr_info->sin_addr));
                printf("Allocating a client struct.\n");
		client_t *client = (client_t *)malloc(sizeof (client_t));
		client->clientSocket = clientSocket;
		client->socket_info = client_addr_info;
		pthread_t client_thread;
        struct ThreadArgs thread_args;
        thread_args.server = server;
        thread_args.client = client;
                printf("In main, creating a client thread...\n");
		int rc = pthread_create(&client_thread, NULL, client_session, 
			(void*)&thread_args);
		if (rc)
		{
			std::cerr << "return code from pthread_create() is " << rc <<  std::endl;
			continue;
		}
                printf("In main, detaching the client thread.\n");
		int detach_val = pthread_detach(client_thread);
		if (detach_val)
			std::cerr << "pthread_detach returned " << detach_val << std::endl;

	}

	return 0;
}
