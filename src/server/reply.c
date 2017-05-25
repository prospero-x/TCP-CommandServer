#include "messages.h"
#include "reply.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef char *(*reply_handler)(ucirc_message_t *message);

#define UCIRC_REPLY_HANDLER_ENTRY(NAME) { NAME, construct_ ## NAME}

struct reply_handler_entry
{
	const char *name;
	reply_handler func;
};


char *construct_ERROR_RESPONSE(ucirc_message_t *message);
char *construct_FLOAT_QUERY_RESPONSE(ucirc_message_t *message);
char *construct_INT_QUERY_RESPONSE(ucirc_message_t *message);
char *construct_MODIFY_SUCCESS_RESPONSE(ucirc_message_t *message);
char *construct_TEC_SET_RESPONSE(ucirc_message_t *message);
char *construct_FILE_DOES_NOT_EXIST(ucirc_message_t *message);
char *construct_TIME_DOES_NOT_EXIST(ucirc_message_t *message);

struct reply_handler_entry ucirc_reply_handlers[] = {
	UCIRC_REPLY_HANDLER_ENTRY(ERROR_RESPONSE),
	UCIRC_REPLY_HANDLER_ENTRY(FLOAT_QUERY_RESPONSE),
	UCIRC_REPLY_HANDLER_ENTRY(INT_QUERY_RESPONSE),
	UCIRC_REPLY_HANDLER_ENTRY(MODIFY_SUCCESS_RESPONSE),
        UCIRC_REPLY_HANDLER_ENTRY(TEC_SET_RESPONSE),
        UCIRC_REPLY_HANDLER_ENTRY(FILE_DOES_NOT_EXIST),
        UCIRC_REPLY_HANDLER_ENTRY(TIME_DOES_NOT_EXIST),
};

char *construct_reply(ucirc_message_t *message, const char *rc)
{
	int num_handlers = sizeof(ucirc_reply_handlers) / sizeof(struct reply_handler_entry);
	for (int i = 0; i < num_handlers; i++)
	{
		if (!strcmp(ucirc_reply_handlers[i].name, rc))
		{
			return ucirc_reply_handlers[i].func(message);
		}
	}
        return ERROR_RESPONSE;	
}

char *construct_ERROR_RESPONSE(ucirc_message_t *message)
{
	char *rv = (char*)malloc(sizeof(char)*ERROR_RESPONSE_SIZE);
	sprintf(rv, "?\r");
	return rv;
}

char *construct_FLOAT_QUERY_RESPONSE(ucirc_message_t *message)
{
	char *rv = (char*)malloc(sizeof(char)*QUERY_RESPONSE_SIZE);
	sprintf(rv, "*%f\r", message->r_float);
	return rv;
}

char *construct_INT_QUERY_RESPONSE(ucirc_message_t *message)
{
	char *rv = (char*)malloc(sizeof(char)*QUERY_RESPONSE_SIZE);
	sprintf(rv, "*%d\r", message->r_int);
	return rv;
}

char *construct_MODIFY_SUCCESS_RESPONSE(ucirc_message_t *message)
{
	char *rv = (char*)malloc(sizeof(char)*SUCCESS_RESPONSE_SIZE);
	sprintf(rv, "*\r");
	return rv;
}

char *construct_TEC_SET_RESPONSE(ucirc_message_t *message)
{
        char *rv = (char*)malloc(sizeof(char)*TEC_SET_RESPONSE_SIZE);
        sprintf(rv, "*%s\r", message->r_string);
        return rv;
}

char *construct_FILE_DOES_NOT_EXIST(ucirc_message_t *message)
{
       char *rv = (char*)malloc(sizeof(char)*ERROR_RESPONSE_SIZE);
       sprintf(rv, "@\r");
       return rv;
}

char *construct_TIME_DOES_NOT_EXIST(ucirc_message_t *message)
{
       char *rv = (char*)malloc(sizeof(char)*ERROR_RESPONSE_SIZE);
       sprintf(rv, "^\r");
       return rv;
}
