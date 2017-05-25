#ifndef REPLY_H
#define REPLY_H

#include "messages.h"

#define ERROR_RESPONSE 			"00"
#define FLOAT_QUERY_RESPONSE 		"01"
#define INT_QUERY_RESPONSE       	"02"
#define MODIFY_SUCCESS_RESPONSE 	"03"
#define TEC_SET_RESPONSE 		"04"
#define FILE_DOES_NOT_EXIST		"05"
#define TIME_DOES_NOT_EXIST             "06"

#define ERROR_RESPONSE_SIZE         3
#define SUCCESS_RESPONSE_SIZE       3
#define QUERY_RESPONSE_SIZE         30
#define TEC_SET_RESPONSE_SIZE       60



char *construct_reply(ucirc_message_t *message, const char *rc);

#endif
