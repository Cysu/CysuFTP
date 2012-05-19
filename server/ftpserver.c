#include "ftpserver.h"

int conn_socket, pasv_socket, data_socket;

char command[BUFFER_SIZE];
char arg[BUFFER_SIZE];

int addr, port;

void ftpserver_init(int sock) {
    conn_socket = sock;
    pasv_socket = -1;
    data_socket = -1;

    addr = get_addr(conn_socket);
}

void ftpserver_welcome() {
    send_msg(conn_socket, REP_WELCOME, RC_SERVICE_READY);
    Log(REPLY, REP_WELCOME, RC_SERVICE_READY);
}

void ftpserver_wait() {
    recv_msg(conn_socket, command, BUFFER_SIZE);
    Log(COMMAND, command);
}

void ftpserver_clean() {
    if (socket_close(data_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
    if (socket_close(pasv_socket) < 0)
        Log(ERROR, ERR_SOCKET_CLOSE);
}

void ftpserver_sendfile(FILE* file) {
    send_msg(conn_socket, REP_TRANS_BEGIN, RC_OPEN_DATA_CONN);
    data_socket = socket_accept(pasv_socket);
    send_file(data_socket, file);
    send_msg(conn_socket, REP_TRANS_END, RC_CLOSE_DATA_CONN);
    ftpserver_clean();
}

void ftpserver_recvfile(FILE* file) {
    send_msg(conn_socket, REP_TRANS_BEGIN, RC_OPEN_DATA_CONN);
    data_socket = socket_accept(pasv_socket);
    recv_file(data_socket, file);
    send_msg(conn_socket, REP_TRANS_END, RC_CLOSE_DATA_CONN);
    ftpserver_clean();
}

void ftpserver_exec() {

    COMMAND_TYPE cmd = get_cmd(command);
    get_arg(command, arg);

    char buf[BUFFER_SIZE];
    FILE* sys_pipe = NULL;
    FILE* file = NULL;

    switch (cmd) {
        case QUIT:
            if (socket_close(conn_socket) < 0)
                Log(ERROR, ERR_SOCKET_CLOSE);
            ftpserver_clean();
            Log(SYSTEM, SYS_QUIT_SUCC);
            exit(EXIT_SUCCESS);

        case UNKNOWN:
            send_msg(conn_socket, REP_UNKNOWN, RC_CMD_NOT_IMPL);
            Log(REPLY, REP_UNKNOWN, RC_CMD_NOT_IMPL);
            break;

        case HELP:
            send_msg(conn_socket, REP_HELP, RC_HELP);
            Log(REPLY, REP_HELP, RC_HELP);
            break;

        case USER:
            send_msg(conn_socket, REP_USER_LOGIN, RC_USER_LOGIN);
            Log(REPLY, REP_USER_LOGIN, RC_USER_LOGIN);
            break;

        case PWD:
            getcwd(arg, BUFFER_SIZE);
            send_msg(conn_socket, REP_PWD, RC_PATH_CREATED, arg);
            Log(REPLY, REP_PWD, RC_PATH_CREATED);
            break;

        case CWD:
            if (!chdir(arg)) {
                send_msg(conn_socket, REP_CWD_SUCC, RC_FILE_ACT_SUCC, arg);
                Log(REPLY, REP_CWD_SUCC, RC_FILE_ACT_SUCC, arg);
            } else {
                send_msg(conn_socket, REP_CWD_FAIL, RC_FILE_ACT_FAIL, arg);
                Log(REPLY, REP_CWD_FAIL, RC_FILE_ACT_FAIL, arg);
            }
            break;

        case TYPE:
            send_msg(conn_socket, REP_TYPE_SUCC, RC_CMD_SUCC);
            Log(REPLY, REP_TYPE_SUCC, RC_CMD_SUCC);
            break;

        case PASV:
            if ((pasv_socket = socket_listen(0)) < 0)
                die(ERR_SOCKET_LISTEN);
            port = get_port(pasv_socket);
            if ((pasv_socket = socket_listen(port)) < 0)
                die(ERR_SOCKET_LISTEN);

            send_msg(conn_socket, REP_PASV_SUCC, RC_PASV_SUCC,
                    addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, addr>>24, port>>8, port&0xff);
            Log(REPLY, REP_PASV_SUCC, RC_PASV_SUCC,
                    addr&0xff, (addr>>8)&0xff, (addr>>16)&0xff, addr>>24, port>>8, port&0xff);
            break;

        case LIST:
            sprintf(buf, "ls -l %s", arg);
            sys_pipe = popen(buf, "r");

            ftpserver_sendfile(sys_pipe);

            pclose(sys_pipe);
            Log(REPLY, REP_LIST_SUCC);
            break;

        case RETR:
            file = fopen(arg, "rb");
            if (!file) {
                send_msg(conn_socket, REP_FILE_FAIL, RC_FILE_ACT_FAIL, arg);
                Log(ERROR, ERR_FILE_OPEN);
                ftpserver_clean();
            } else {
                ftpserver_sendfile(file);
            }
            fclose(file);
            Log(REPLY, REP_RETR_SUCC);
            break;

        case STOR:
            file = fopen(arg, "wb");
            if (!file) {
                send_msg(conn_socket, REP_FILE_FAIL, RC_FILE_ACT_FAIL, arg);
                Log(ERROR, ERR_FILE_OPEN);
                ftpserver_clean();
            } else {
                ftpserver_recvfile(file);
            }
            fclose(file);
            Log(REPLY, REP_STOR_SUCC);
            break;
    }
}

void ftpserver_process(int sock) {
    ftpserver_init(sock);
    ftpserver_welcome();

    while (1) {
        ftpserver_wait();
        ftpserver_exec();
    }
}

