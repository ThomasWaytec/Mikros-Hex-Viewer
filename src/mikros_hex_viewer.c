#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#ifdef _WIN32
    #include <Windows.h>
    
    size_t get_terminal_width() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(hConsole, &csbi);
        size_t terminal_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return terminal_width;
    }

#endif

#ifdef linux
    #include <sys/ioctl.h>
    #include <unistd.h>
    
    size_t get_terminal_width() {
        struct winsize ws;
        
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
        size_t terminal_width = ws.ws_col;

        return terminal_width;
    }
#endif

#include "error.h"
#include "file.h"
#include "char_len_constants.h"
#include "datatype_len.h"
#include "data_formats.h"
#include "data_unit.h"


#define MAX_LINE_LEN get_terminal_width()

extern data_format_t bin;
extern data_format_t hex;
extern data_format_t dec;
extern data_format_t DATA_FORMATS_MAP[];

void initialize_data_unit(data_unit_t* data_unit) {

    
    for (size_t i = 0; i < data_unit->data_formats_len; i++)
    {
        data_unit->len += data_unit->data_formats[i].len;
    }

    /* determine the appropriate group size */
    if (data_unit->data_formats_len > 1) {data_unit->group_size = 1;}
    else {
        if (data_unit->len <= 3)
        {
            data_unit->group_size = 4;
        }
        else if (data_unit->len == 4) {
            data_unit->group_size = 3;
        }
        else if (data_unit->len > 4 && data_unit->len < 8) {
            data_unit->group_size = 2;
        }
        else {
            data_unit->group_size = 1;
        }

    }


    /* determine group separator */
    if (data_unit->data_formats_len == 1)
    {
        data_unit->group_sep = " ";
    }
    
    else {
        if (data_unit->len < 10) {
            data_unit->group_sep = " | ";
        }
        else {
            data_unit->group_sep = " ";
        }
    }
    
    /* calculate group len */
    data_unit->group_len = data_unit->len*data_unit->group_size + strlen(data_unit->group_sep);
    


}
    
void print_data_unit(data_unit_t* data_unit, size_t byte) {

    /* call the print function for all the data formats */
    for (size_t i = 0; i < data_unit->data_formats_len; i++)
    {
        data_unit->data_formats[i].print(byte);   
    }
}
    
void print_header(size_t current_line, double lines, double units_per_line) {

        size_t units_printed = units_per_line*(double)current_line;
        size_t units_printed_padding = size_t_len(units_per_line*lines);


        printf("%0*u| ", units_printed_padding, units_printed);

}

int main(int argc, char* argv[]) {



    char* chosen_data_formats = NULL;
    size_t chosen_data_formats_len = 0;

    char* FILEPATH = NULL;
    char* arg;
    /* parse coommand-line arguments */
    for (size_t i = 1; i < argc; i++) {   
        arg = argv[i];

        
        if (arg[0] == '-')
        {   
            /* if not a one letter argument (i.e. -h) */   
            if (strlen(arg) != 2) {fatal_error("Unknown argument: \"%s\"", arg);}
            
            /* if not found among the data formats */
            if (!DATA_FORMATS_MAP[arg[1]].exist) {fatal_error("Unknown argument: \"%s\"", arg);}
            
            chosen_data_formats_len += 1;
            chosen_data_formats = realloc(chosen_data_formats, chosen_data_formats_len);

            chosen_data_formats[chosen_data_formats_len - 1] = arg[1];    
                
        }

        

        /* if a non-switch argument */
        else if (arg[0] != '-') {
            /* more than one filepath arguments given */
            if (FILEPATH != NULL) {fatal_error("Too many non-switch arguments: \"%s\" ...", arg);}

            FILEPATH = arg;
        }
    }

    if (FILEPATH == NULL) {fatal_error("No file argument given.");}
    
    /* set default data format if none chosen */
    if (chosen_data_formats == NULL) {
        chosen_data_formats_len += 1;
        chosen_data_formats = realloc(chosen_data_formats, chosen_data_formats_len);

        chosen_data_formats[chosen_data_formats_len - 1] = HEXADECIMAL;
    }

    


    
    /* try to open file */
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {fatal_error("File not found or doesn't exist: \"%s\"", FILEPATH);}
    const size_t FILE_SIZE = get_file_size(file);



    exit(0);

    data_unit_t data_unit;

    initialize_data_unit(&data_unit);


    /* defined as double for easier calculations */
    double header_len = size_t_len(FILE_SIZE) + VERTICAL_LINE_LEN + SPACE_LEN;
    double payload_len = MAX_LINE_LEN - header_len;
    
    double unit_groups_per_line = floor((payload_len - NEW_LINE_LEN)/data_unit.group_len);
    double units_per_line = floor(unit_groups_per_line*data_unit.group_size);

    size_t lines = (size_t)ceil((double)FILE_SIZE/units_per_line);


    /* debug dataunit */
    printf("data_format[0]=%c\n", data_unit.data_formats[0]);
    printf("data_format_len=%d\n", data_unit.data_formats_len);
    printf("len=%f\n", data_unit.len);

    printf("\n");
    printf("max=%d\n", MAX_LINE_LEN);
    printf("header=%f\n", header_len);
    printf("payload=%f\n", payload_len);

    printf("units_per_line=%f\n", units_per_line);
    printf("unit_group_per_line=%f\n", unit_groups_per_line);
    printf("lines=%d\n", lines);
    
    
    /* set up stdout full buffering */
    void* stdout_buffer = NULL;
    setvbuf(stdout, stdout_buffer, _IOFBF, INT_MAX);
    





    size_t byte; // has to be int to be able to check for EOF
    for (size_t line = 0; line < lines && byte != EOF; line++)
    {
        print_header(line, lines, units_per_line);

        for (size_t i = 0; i < unit_groups_per_line && byte != EOF; i++)
        {

            for (size_t j = 0; j < data_unit.group_size && (byte = fgetc(file)) != EOF; j++) {
               
                print_data_unit(&data_unit, byte);
            }
            if (byte != EOF) {printf("%s", data_unit.group_sep);}
            
        }       
        printf("\n");
    }

    fclose(file);
    return 0;   
}
