#include <stdio.h>

const char *help_message = "mikros: View and analyze files in various formats (hexadecimal, binary, decimal, and character) with this hex viewer.\n" 
    "\n"
    "Usage: mikros FILE [OPTIONS]\n"
    "\n"
    "Positional Arguments:\n"
    "  FILE            The name or path of the file for analysis.\n"
    "\n"
    "OPTIONS:\n"
    "  -h, --help      Display this help message and exit.\n"
    "  -x              Display data in hexadecimal format (default).\n"
    "  -d              Display data in decimal format.\n"
    "  -b              Display data in binary format.\n"
    "  -c              Display data as characters.\n"
    "  --buffer        Enable stdout buffering for faster output (no Ctrl+C interruption).\n"
    "\n"
    "Data format options can be combined without double dashes, e.g., -dxcb for decimal, hexadecimal, character and binary format.\n"
    "\n"
    "Example Usage:\n"
    "   mikros file.jpeg\n"
    "   mikros file.bin -dxcb\n"
    "   mikros -d --buffer folder/file.txt -xb\n";


void print_help_message(void) {

    printf("%s\n", help_message);
}

void print_usage(void) {
    
    const char* USAGE = "\n\nUsage: mikros FILE [OPTIONS]\nUse -h for help.";
    printf("%s\n", USAGE);
}