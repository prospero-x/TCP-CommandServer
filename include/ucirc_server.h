#ifndef UCIRC_SERVER_H
#define UCIRC_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#ifndef TRUE
    #define TRUE 1
#endif 

#ifndef FALSE
    #define FALSE 0
#endif 

#define BUFFER_SIZE 16384
#define HOST_BUFFER_SIZE 200
#define IP_LENGTH 16
#define SERVER_BUFFER_SIZE 200
#define PORT "9999"

#define LOG_INDICATOR_FILE "/root/log_night"
#define LOG_INDICATOR_COMMAND_LENGTH 100

#define INTERVAL_FILE "/root/interval"
#define INTERVAL_FILE_COMMAND_LENGTH 100

#define SINGLETON_PROGRAM "/root/bin/single_night_picture.sh &"

void update_log_indicator_file(int night);
int get_interval_from_file();
void set_interval_file(int interval);
void send_singleton();



typedef struct {
	int interval;
	int night;
}ucirc_server_t;

#endif /* UCIRC_SERVER_H */
