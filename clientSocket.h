#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_
#include <sys/socket.h>
typedef struct ClientSocket__{
    int client_fd;
		char ip[32];
    struct sockaddr_in* client_addr;
}ClientSocket;
#endif
