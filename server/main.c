#include <signal.h>

#include "ftpserver.h"

int server_socket, client_socket;
int pid;

void quit() {
    if (socket_close(server_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
    if (socket_close(client_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, quit);
    signal(SIGTERM, quit);

    server_socket = -1;
    client_socket = -1;

    if ((server_socket = socket_listen(21)) < 0) 
        die(ERR_SOCKET_LISTEN);

    while (1) {
        Log(SYSTEM, SYS_WAIT_CLIENT);

        if ((client_socket = socket_accept(server_socket)) < 0) {
            Log(ERROR, ERR_SOCKET_ACCEPT);
            continue;
        }

        pid = fork();
        if (pid == -1) {
            Log(ERROR, ERR_FORK);
        } else if (pid == 0) {
            ftpserver_process(client_socket);
        } else {
            if (socket_close(client_socket) < 0)
                Log(ERROR, ERR_SOCKET_CLOSE);
        }
    }

    return 0;
}

