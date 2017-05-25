#ifndef HANDLERS_H
#define HANSLERS_H

#include "ucirc_server.h"
#include "client.h"
#include "messages.h"

const char *ucirc_handle(ucirc_server_t *server, ucirc_message_t *message);

#endif
