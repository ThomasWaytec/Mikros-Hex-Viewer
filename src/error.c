#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void fatal_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);


    fprintf(stderr, "\nError: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");


    va_end(args);

    exit(EXIT_FAILURE);
}

void unknown_arg_error(char* arg) {
    fatal_error("Unknown argument: \"%s\"", arg);
}