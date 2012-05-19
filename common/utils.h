#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "const.h"

void Log(const char* type, const char* fmt, ...);
void die(const char* die_msg);

COMMAND_TYPE get_cmd(const char* command);
void get_arg(const char* command, char* arg);

void read_line(char* buf);

void print_file(const char* file_name);

#endif // UTILS_H
