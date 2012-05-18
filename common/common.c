#include "common.h"

int socket_listen(int *sock, int port) {
    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(21);

    if (bind(*sock, (sockaddr*)&addr, sizeof addr) < 0) return -1;

    if (listen(*sock, 10) < 0) return -1;

    return *sock;
}

int socket_accept(int *sock) {
    sockaddr_in addr;
    socklen_t addr_len = sizeof addr;
    return accept(*sock, (sockaddr*)&addr, &addr_len);
}

int socket_close(int *sock) {
    if (*sock < 0) return 0;
    int ret = close(*sock);
    *sock = -1;
    return ret;
}

