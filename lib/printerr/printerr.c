#include "printerr.h"

#if PRINT_ERR == 1

void _printfError(PRINTERR_ANSI_COLOR_ENUM type, const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("%s", printerrColorArray[type]);
    vprintf( format, args);
    printf("\x1b[0m");
    va_end(args);
}

#else


#endif
