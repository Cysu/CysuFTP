#include <signal.h>

#include "ftpclient.h"

int conn_socket;

int main(int argc, char* argv[]) {
    signal(SIGINT, ftpclient_quit);
    signal(SIGTERM, ftpclient_quit);

    conn_socket = -1;

    int port = 21;
    char* host = "127.0.0.1";

    if (argc != 2 && argc != 3) {
        printf("Usage: %s [host[port]], default host=127.0.0.1 port=21\n", argv[0]);
    } else if (argc == 2) {
        host = argv[1];
    } else if (argc == 3) {
        host = argv[1];
        port = atoi(argv[2]);
    }

    if ((conn_socket = socket_connect(host, port)) < 0)
        die(ERR_SOCKET_CONNECT);

    ftpclient_process(conn_socket);

    return 0;
}

