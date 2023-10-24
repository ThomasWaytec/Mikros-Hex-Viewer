#include <stdio.h>

const char *help_message = "Usage: mikros FILE [OPTIONS]\n"
    "View the hexadecimal representation of a file in the terminal.\n"
    "\n"
    "Options:\n"
    "  -x               Display data in hexadecimal format (default).\n"
    "  -d               Display data in decimal format.\n"
    "  -b               Display data in binary format.\n"
    "  -c               Display data as characters.\n"
    "  -h, --help       Display this help message and exit.\n"
    "  --buffer         Enable stdout buffering for faster output (no Ctrl+C interruption).\n"
    "Data format options can be combined without double dashes, e.g., -dxcb for decimal, hexadecimal, character and binary format.\n"
    "\n"
    "Examples:\n"
    "   mikros file.jpeg\n"
    "   mikros file.bin -dxcb\n"
    "   mikros -d --buffer folder/file.txt -xb\n";


void print_help_message(void) {

    printf("%s\n", help_message);   
}