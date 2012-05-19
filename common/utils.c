#include "utils.h"

void Log(const char* type, const char* fmt, ...) {
    printf("%s", type);
    va_list vl;
    va_start(vl, fmt);
    vprintf(fmt, vl);
    va_end(vl);
}

void die(const char* die_msg) {
    Log(ERROR, die_msg);
    exit(EXIT_FAILURE);
}

COMMAND_TYPE get_cmd(const char* command) {
    char buf[10];
    char* cmd = buf;
    while (*command != ' ' && *command != '\r') *cmd++ = *command++;
    *cmd = '\0';

    int i;
    COMMAND_TYPE ret = UNKNOWN;
    for (i = 0; i < (int)NR_COMMAND; i ++) {
        if (!strcasecmp(buf, COMMAND_STRING[i])) {
            ret = (COMMAND_TYPE)i;
            break;
        }
    }

    return ret;
}

void get_arg(const char* command, char* arg) {
    while (*command != ' ' && *command != '\r') command++;
    if (*command != '\r') {
        command++;
        while (*command != '\r') *arg++ = *command++;
    }
    *arg = '\0';
}

void read_line(char* buf) {
    char c;
    while (1) {
        scanf("%c", &c);
        if (c == '\n') break;
        *buf++ = c;
    }
    *buf = '\0';
}

void print_file(const char* file_name) {
    FILE* file = fopen(file_name, "r");
    char c;
    while (fscanf(file, "%c", &c) != EOF)
        printf("%c", c);
    fclose(file);
}
