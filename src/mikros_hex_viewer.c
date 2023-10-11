#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

#include "char_lengths.h"
#include "data_formats.h"
#include "data_unit.h"


#define MAX_LINE_LEN get_terminal_width()

#define PCT_SIGN_LEN 1.0   /* PCT = PERCENTAGE */
#define COMPLETION_PCT_LEN (3.0 + PCT_SIGN_LEN)


/* from data_formats.c */
extern char SUPPORTED_DATA_FORMATS[];
extern data_format_t bin;
extern data_format_t hex;
extern data_format_t dec;

void fatal_error(const char* message)
{
    fprintf(stderr,"\nError: %s\n", message);
    exit(EXIT_FAILURE);
}

size_t int_len(size_t number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;
}

size_t doube_len(double number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;


}

void initialize_data_unit(data_unit_t* data_unit, const char CHOSEN_DATA_FORMATS[], const size_t CHOSEN_DATA_FORMATS_LEN) {


    data_unit->data_formats = calloc(CHOSEN_DATA_FORMATS_LEN, sizeof(char));
    data_unit->data_formats_len = CHOSEN_DATA_FORMATS_LEN;
    
    for (size_t i = 0; i < CHOSEN_DATA_FORMATS_LEN; i++)
    {

        
        switch (CHOSEN_DATA_FORMATS[i])
        {

            case HEXADECIMAL:
                data_unit->data_formats[i] = HEXADECIMAL;
                data_unit->len += hex.len;
                break;

            
            case BINARY:        
                data_unit->data_formats[i] = BINARY;
                data_unit->len += bin.len;
                break;

            case DECIMAL:
                data_unit->data_formats[i] = DECIMAL;
                data_unit->len += dec.len;
                break;

            default:
                break;
        }

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

    /* calculate group len */
    data_unit->group_len = data_unit->len*data_unit->group_size + SPACE_LEN;
    


}
    
void print_data_unit(data_unit_t* data_unit, size_t byte) {

    /* call the appropriate print function for the different data formats */
    for (size_t i = 0; i < data_unit->data_formats_len; i++)
    {   
        switch (data_unit->data_formats[i]) {

            case HEXADECIMAL:
                print_hex(byte);
                break;

                
            case BINARY:
                print_bin(byte);
                break;

            case DECIMAL:
                print_dec(byte);
                break;
        }
   }
    

}

const size_t get_file_size(FILE* file) {

    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);            
    fseek(file, 0, SEEK_SET);

    return FILE_SIZE;
}

void print_header(size_t current_line, double lines, double units_per_line) {
        size_t completion_pct = (current_line + 1)/lines*100;
        size_t completion_pct_padding = COMPLETION_PCT_LEN - PCT_SIGN_LEN;

        size_t units_printed = units_per_line*(double)current_line;
        size_t units_printed_padding = int_len(units_per_line*lines);


        printf("%0*u%% %0*u| ", completion_pct_padding, completion_pct, units_printed_padding, units_printed);

}


int main(int argc, char* argv[]) {

    const char SELECTED_DATA_FORMATS[] = {DECIMAL};
    const size_t SELECTED_DATA_FORMATS_LEN =  1;


    
    data_unit_t data_unit;
    initialize_data_unit(&data_unit, SELECTED_DATA_FORMATS, SELECTED_DATA_FORMATS_LEN);
    printf("data_format[0]=%c\n", data_unit.data_formats[0]);
    printf("data_unit.len=%f\n", data_unit.len);
    printf("data_unit.group_size=%f\n", data_unit.group_size);
    printf("data_unit.group_len=%f\n", data_unit.group_len);

    

    /*
    validate coommand-line arguments count
    if ((argc - 1) != 1) {
        char* argc_buffer = calloc(sizeof(char), 54 + int_len(argc) + 1);
        sprintf(argc_buffer, "Program takes 1 command-line argument but %d were given.", argc - 1);
        fatal_error(argc_buffer);
    }
    const char* FILEPATH = argv[1];
    */

    const char FILEPATH[] = "test_files/jpeg/test_4.jpg";
    /* try to open file */
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {fatal_error("Cannot find or open file.");}



    const size_t FILE_SIZE = get_file_size(file);


    /* defined as double for easier calculations */
    double header_len = COMPLETION_PCT_LEN + SPACE_LEN + int_len(FILE_SIZE) + VERTICAL_LINE_LEN + SPACE_LEN;
    double payload_len = MAX_LINE_LEN - header_len;
    
    double unit_groups_per_line = floor((payload_len - NEW_LINE_LEN)/data_unit.group_len);
    double units_per_line = floor(unit_groups_per_line*data_unit.group_size);

    size_t lines = (size_t)ceil((double)FILE_SIZE/units_per_line);

    printf("\n");
    printf("max=%d\n", MAX_LINE_LEN);
    printf("header=%f\n", header_len);
    printf("payload=%f\n", payload_len);

    printf("units_per_line=%f\n", units_per_line);
    printf("unit_group_per_line=%f\n", unit_groups_per_line);
    printf("lines=%d\n", lines);
    
    /*
    set up stdout full buffering 
    void* stdout_buffer = NULL;
    setvbuf(stdout, stdout_buffer, _IOFBF, INT_MAX);
    */





    size_t byte; // has to be int to be able to check for EOF
    for (size_t line = 0; line < lines; line++)
    {
        print_header(line, lines, units_per_line);

        for (size_t _ = 0; _ < unit_groups_per_line; _++)
        {

            for (size_t _ = 0; _ < data_unit.group_size && (byte = fgetc(file)) != EOF; _++) 
            {
                print_data_unit(&data_unit, byte);
            }
            printf(" ");
            
        }       
        printf("\n");
    }

    fclose(file);
    return 0;   
}
