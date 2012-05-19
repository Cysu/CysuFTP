#ifndef CONST_H
#define CONST_H

/* Constants */
#define BUFFER_SIZE 1024

/* Log type */
#define ERROR       "Error: "
#define SYSTEM      "System: "
#define COMMAND     "Command: "
#define REPLY       "Reply: "

/* Error message */
#define ERR_FORK            "fork failed\n"
#define ERR_SOCKET_LISTEN   "socket listen failed\n"
#define ERR_SOCKET_ACCEPT   "socket accept failed\n"
#define ERR_SOCKET_CLOSE    "socket close failed\n"
#define ERR_SOCKET_SEND     "socket send failed\n"
#define ERR_SOCKET_RECV     "socket recv failed\n"
#define ERR_FILE_OPEN       "file open failed\n"

/* System message */
#define SYS_WAIT_CLIENT     "waiting client connection\n"
#define SYS_QUIT_SUCC       "quit success\n"

/* Command message */

/* Reply message */
#define REP_WELCOME         "%d Service ready for new user. Provided by CysuFTP.\r\n"
#define REP_HELP            "%d quit help user pwd cwd type pasv retr stor list\r\n"
#define REP_USER_LOGIN      "%d User logged in, proceed.\r\n"
#define REP_PWD             "%d %s is the current dir.\r\n"
#define REP_CWD_SUCC        "%d Change to %s.\r\n"
#define REP_CWD_FAIL        "%d Failed changed to %s.\r\n"
#define REP_TYPE_SUCC       "%d Type remains unchanged.\r\n"
#define REP_PASV_SUCC       "%d Entering Passive Mode (%d,%d,%d,%d,%d,%d).\r\n"
#define REP_TRANS_BEGIN     "%d Data transfer begins.\r\n"
#define REP_TRANS_END       "%d Data transfer ends.\r\n"
#define REP_FILE_FAIL       "%d File %s unavailable.\r\n"
#define REP_UNKNOWN         "%d Command not implemented.\r\n"
#define REP_LIST_SUCC       "List command success.\n"
#define REP_RETR_SUCC       "Retr command success.\n"
#define REP_STOR_SUCC       "Stor command success.\n"

/* Reply code */
#define RC_OPEN_DATA_CONN   150
#define RC_CMD_SUCC         200
#define RC_HELP             214
#define RC_SERVICE_READY    220
#define RC_CLOSE_DATA_CONN  226
#define RC_PASV_SUCC        227
#define RC_USER_LOGIN       230
#define RC_FILE_ACT_SUCC    250
#define RC_PATH_CREATED     257
#define RC_CMD_NOT_IMPL     520
#define RC_FILE_ACT_FAIL    550

/* Commands */
typedef enum COMMAND_TYPE {
    UNKNOWN = -1,
    QUIT,
    HELP,
    USER,
    PWD,
    CWD,
    TYPE,
    PASV,
    LIST,
    RETR,
    STOR,
    NR_COMMAND
} COMMAND_TYPE;

const char* COMMAND_STRING[];

#endif // CONST_H
