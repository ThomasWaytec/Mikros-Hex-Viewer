#include <stdio.h>
#include <stdlib.h>

void fatal_error(const char* message)
{
    fprintf(stderr,"\nError: %s\n", message);
    exit(EXIT_FAILURE);
}
