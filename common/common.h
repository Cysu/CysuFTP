#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils.h"

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int socket_listen(int *sock, int port);
int socket_accept(int *sock);
int socket_close(int *sock);

#endif // COMMON_H

