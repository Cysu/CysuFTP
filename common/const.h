#ifndef CONST_H
#define CONST_H

/* Log type */
#define ERROR "Error: "
#define SYSTEM "System: "
#define COMMAND "Command: "
#define RESPONSE "Response: "

/* Error message */
#define ERR_FORK "fork failed\n"
#define ERR_SOCKET_LISTEN "socket listen failed\n"
#define ERR_SOCKET_ACCEPT "socket accept failed\n"
#define ERR_SOCKET_CLOSE "socket close failed\n"

/* System message */
#define SYS_WAIT_CLIENT "waiting client connection\n"

#endif // CONST_H
