#ifndef PRINTERR_H
#define PRINTERR_H

#include <stdarg.h>
#include <stdio.h>

#ifndef PRINT_ERR
#define PRINT_ERR 1
#endif

#if PRINT_ERR == 1

#define printfError(t, ...) _printfError(t, __VA_ARGS__)

#define PRINTERR_ANSI_COLOR_RED     "\x1b[31m"
#define PRINTERR_ANSI_COLOR_GREEN   "\x1b[32m"
#define PRINTERR_ANSI_COLOR_YELLOW  "\x1b[33m"
#define PRINTERR_ANSI_COLOR_BLUE    "\x1b[34m"
#define PRINTERR_ANSI_COLOR_MAGENTA "\x1b[35m"
#define PRINTERR_ANSI_COLOR_CYAN    "\x1b[36m"
#define PRINTERR_ANSI_COLOR_RESET   "\x1b[0m"

static char printerrColorArray[7][9] = {
    PRINTERR_ANSI_COLOR_RED,
    PRINTERR_ANSI_COLOR_GREEN,
    PRINTERR_ANSI_COLOR_YELLOW,
    PRINTERR_ANSI_COLOR_BLUE,
    PRINTERR_ANSI_COLOR_MAGENTA,
    PRINTERR_ANSI_COLOR_CYAN,
    PRINTERR_ANSI_COLOR_RESET
};

typedef enum {
    TERRO,
    TOKAY,
    TWARN,
    TINFO
} PRINTERR_ANSI_COLOR_ENUM;

void _printfError(PRINTERR_ANSI_COLOR_ENUM type, const char *format, ...);

#else

#define printfError(t, ...)

#endif

#endif
