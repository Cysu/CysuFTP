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

