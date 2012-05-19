#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils.h"

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int socket_listen(int port);
int socket_connect(char* host, int port);
int socket_accept(int sock);
int socket_close(int sock);

void send_msg(int sock, const char* fmt, ...);
void recv_msg(int sock, char* buf, int size);

void send_file(int sock, FILE* file);
void recv_file(int sock, FILE* file);

int get_addr(int sock);
int get_port(int sock);

#endif // COMMON_H

