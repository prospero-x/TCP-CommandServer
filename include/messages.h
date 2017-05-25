#ifndef MESSAGES_H
#define MESSAGES_H

#include "simclist.h"
#include "ucirc_server.h"

typedef struct {
    char *command;
    list_t params;
    union {
    	int r_int;
    	float r_float;
    };
    char *r_string;
    int r_type;
}ucirc_message_t;

bool all_white_spaces(char *string);
ucirc_message_t *buff_to_ucirc_message(char *buff);
char *ucirc_process_buffer(ucirc_server_t *server, char *buffer);
void free_ucirc_message(ucirc_message_t *message);

#endif /* MESSAGES_H */
