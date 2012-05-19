#include "common.h"

int socket_listen(int port) {
    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&addr, sizeof addr) < 0) return -1;

    if (listen(sock, 10) < 0) return -1;

    return sock;
}

int socket_connect(char* host, int port) {
    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(host);
    addr.sin_port = htons(port);

    if (connect(sock, (sockaddr*)&addr, sizeof addr) < 0) return -1;

    return sock;
}

int socket_accept(int sock) {
    sockaddr_in addr;
    socklen_t addr_len = sizeof addr;
    return accept(sock, (sockaddr*)&addr, &addr_len);
}

int socket_close(int sock) {
    if (sock < 0) return 0;
    return close(sock);
}

void send_msg(int sock, const char* fmt, ...) {
    char msg[BUFFER_SIZE];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(msg, sizeof(msg), fmt, vl);
    va_end(vl);

    if (send(sock, msg, strlen(msg), 0) < 0)
        die(ERR_SOCKET_SEND);
}

void recv_msg(int sock, char* buf, int size) {
    memset(buf, 0, size);
    if (recv(sock, buf, size, 0) < 0)
        die(ERR_SOCKET_RECV);
}

void send_file(int sock, FILE* file) {
    char data[BUFFER_SIZE];
    int size;
    while ((size = fread(data, 1, BUFFER_SIZE, file)) > 0) {
        if (send(sock, data, size, 0) < 0)
            die(ERR_SOCKET_SEND);
    }
}

void recv_file(int sock, FILE* file) {
    char data[BUFFER_SIZE];
    int size;
    while ((size = recv(sock, data, BUFFER_SIZE, 0)) > 0) {
        fwrite(data, 1, size, file);
    }
    if (size < 0)
        die(ERR_SOCKET_RECV);
}

int get_addr(int sock) {
    sockaddr_in addr;
    socklen_t len = sizeof addr;
    getsockname(sock, (sockaddr*)&addr, &len);
    return addr.sin_addr.s_addr;
}

int get_port(int sock) {
    sockaddr_in addr;
    socklen_t len = sizeof addr;
    getsockname(sock, (sockaddr*)&addr, &len);
    return addr.sin_port;
}

