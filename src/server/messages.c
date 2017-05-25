#include <ctype.h>
#include "handler.h"
#include "messages.h"
#include "simclist.h"
#include "stddef.h"
#include "string.h"
#include "client.h"
#include <stdlib.h>
#include <stdio.h>
#include "reply.h"


/*
Convert a string to a ucirc_message_t. 
*/
ucirc_message_t *buff_to_ucirc_message(char *buff)
{
    int i;
    ucirc_message_t *parsed_message = (ucirc_message_t *)malloc(sizeof(ucirc_message_t));
    memset(parsed_message, 0, sizeof(ucirc_message_t));
  
    /* Corner Case NULL input */
    if (buff == NULL)
        return parsed_message;

    /* Check if only whitespace */
    if (all_white_spaces(buff))
        return parsed_message;

    /* Prepare to parse the message */
    char *save_ptr, *curr_token;
    char *dupstr = strdup(buff);
    list_t params_list;
    list_init(&params_list);


    /* If there is no space, this is a QUERY */
    if (strstr(dupstr, " ") == NULL)
    {
        parsed_message->params = params_list;
        /* Convert the command to upper case */
        int len = strlen(dupstr);
        for (i = 0; i < len; i++)
            dupstr[i] = toupper(dupstr[i]);
        dupstr[len - 1] = '\0';
        parsed_message->command = dupstr;
        return parsed_message;
    }
 
    /* The command is the first word in the message */
    char *command = strtok_r(NULL, " ", &dupstr);
    

    /* Convert the command to upper case */
    for (i = 0; i < strlen(command); i++)
        command[i] = toupper(command[i]);
    parsed_message->command = strdup(command);

   
    /* Parse the parameters */
    while (strstr(dupstr, " ") != NULL)
    {
       curr_token = strdup(strtok_r(NULL, " ", &dupstr));
       printf("curr_token: %s\n", curr_token);
       list_append(&params_list, curr_token);
       if (all_white_spaces(dupstr))
           break;
    }  
    

    /* Append final parameter */
    list_append(&params_list, dupstr);
    parsed_message->params = params_list;
    return parsed_message;
}

/* Does the buffer have the correct format? */
bool verify_buffer(char *buffer)
{
    int len = strlen(buffer);
    if (buffer[0] != '$' || buffer[len - 1] != '\r')
        return FALSE;
    return TRUE;
}

char *ucirc_process_buffer(ucirc_server_t *server, char *buffer)
{
    if (verify_buffer(buffer))
    {
        ucirc_message_t *rc_message = buff_to_ucirc_message(buffer + 1);
        const char *rc = ucirc_handle(server, rc_message);
        char *reply = construct_reply(rc_message, rc);
        list_destroy(&rc_message->params);
        if (rc_message->r_string != NULL)
        {
            printf("freeing...\n");
            free(rc_message->r_string);
            printf("freed!\n");
        }
        free(rc_message);
        return reply;
    }
    else
        return construct_reply(NULL, ERROR_RESPONSE);
}

bool all_white_spaces(char *string)
{ 
    int i;
    int msg_len = strlen(string);
        /* Check if there's only whitespace */
        for (i = 0; i < msg_len; i++)
        {
            if (*(string + i) != ' ')
                return FALSE;
        }
    return TRUE;  
}
