#ifndef USER_H
#define USER_H

#include "ucirc_server.h"


typedef struct
{
   int clientSocket;
   struct sockaddr_in *socket_info;
   bool received_quit;
} client_t;

#endif /* USER _H */
