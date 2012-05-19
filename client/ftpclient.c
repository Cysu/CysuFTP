#include "ftpclient.h"

int conn_socket, data_socket;

char command[BUFFER_SIZE];
char arg[BUFFER_SIZE];
char reply[BUFFER_SIZE];

void ftpclient_init(int sock) {
    conn_socket = sock;
    data_socket = -1;
}

void ftpclient_quit() {
    if (socket_close(conn_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
    if (socket_close(data_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
    exit(EXIT_SUCCESS);
}

void ftpclient_wait() {
    recv_msg(conn_socket, reply, BUFFER_SIZE);
    Log(REPLY, reply);
}

void ftpclient_pasv() {
    int a[6];
    sscanf(reply, "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).",
            &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);
    char host[BUFFER_SIZE];
    int port;
    sprintf(host, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
    port = (a[4]<<8) + a[5];
    if ((data_socket = socket_connect(host, port)) < 0)
        die(ERR_SOCKET_CONNECT);
}

void ftpclient_list() {
    /* Save to a temp file. */
    char file_name[BUFFER_SIZE];
    sprintf(file_name, "cysuftpc_%d.tmp", data_socket);
    FILE* tmp_file = fopen(file_name, "w");
    recv_file(data_socket, tmp_file);
    ftpclient_wait();
    fclose(tmp_file);

    /* Print file content. */
    print_file(file_name);

    /* Delete the temp file. */
    char sys_func[BUFFER_SIZE];
    strcpy(sys_func, "rm -f ");
    strcat(sys_func, file_name);
    system(sys_func);

    if (socket_close(data_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
}

void ftpclient_retr() {
    FILE* file = fopen(arg, "wb");
    recv_file(data_socket, file);
    ftpclient_wait();
    fclose(file);

    if (socket_close(data_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
}

void ftpclient_stor() {
    FILE* file = fopen(arg, "rb");
    if (!file) {
        Log(ERROR, ERR_FILE_OPEN);
        if (socket_close(data_socket) < 0)
            Log(ERROR, ERR_SOCKET_CLOSE);
        return;
    }

    send_file(data_socket, file);
    fclose(file);
    if (socket_close(data_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);

    ftpclient_wait();
}

void ftpclient_exec() {
    /* Send command */
    strcat(command, "\r\n");
    send_msg(conn_socket, command);

    COMMAND_TYPE cmd = get_cmd(command);
    get_arg(command, arg);

    if (cmd == QUIT) 
        ftpclient_quit();

    ftpclient_wait();

    switch (cmd) {
        case PASV:
            ftpclient_pasv();
            break;

        case LIST:
            ftpclient_list();
            break;

        case RETR:
            ftpclient_retr();
            break;

        case STOR:
            ftpclient_stor();
            break;
    }

}

void ftpclient_process(int sock) {
    ftpclient_init(sock);
    ftpclient_wait();

    while (1) {
        printf("ftpclient> ");
        read_line(command);
        ftpclient_exec();
    }
}

