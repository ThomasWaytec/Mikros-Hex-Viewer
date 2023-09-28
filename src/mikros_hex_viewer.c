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

#define MAX_LINE_LEN get_terminal_width()

/* macros are defined as doubles for easier calculations further on */
#define PCT_SIGN_LEN 1.0        /* PCT = PERCENTAGE */
#define SPACE_LEN 1.0
#define VERTICAL_LINE_LEN 1.0
#define HEX_LEN 2.0             /* max. possible length of a byte represented in hexadecimal */
#define HEX_PADDING 2.0 
#define COMPLETION_PCT_LEN 4.0  /* PCT = PERCENTAGE*/

#define FMT_HEX_LEN (HEX_LEN + SPACE_LEN)                               /* FMT = FORMATTED */
#define FMT_HEX_GRUP_SIZE 4.0                                           /* the number offormatted hex values in one group */
#define FMT_HEX_GROUP_LEN (FMT_HEX_LEN*FMT_HEX_GROUP_SIZE + SPACE_LEN)  /* how many characters a formatted hex group takes up */





void fatal_error(const char* message)
{
    fprintf(stderr,"\nError: %s\n", message);
    exit(EXIT_FAILURE);
}

size_t int_len(size_t number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;
}

const size_t get_file_size(FILE* file) {

    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);            
    fseek(file, 0, SEEK_SET);

    return FILE_SIZE;
}

void print_header(size_t line, size_t lines, size_t fmt_hex_per_line) {
        size_t completion_pct = (size_t)(double)(line + 1)/(double)lines*100;
        size_t completion_pct_padding = COMPLETION_PCT_LEN - PCT_SIGN_LEN;

        size_t fmt_hex_printed = (size_t)(double)fmt_hex_per_line*(double)line;
        size_t fmt_hex_printed_padding = int_len((double)fmt_hex_per_line*(double)(lines));


        printf("%0*u%% %0*u| ", completion_pct_padding, completion_pct, fmt_hex_printed_padding, fmt_hex_printed);

}



int main(int argc, char* argv[]) {


    /* validate coommand-line arguments count */
    if ((argc - 1) != 1) {
        char* argc_buffer = calloc(sizeof(char), 54 + integer_length(argc) + 1);
        sprintf(argc_buffer, "Program takes 1 command-line argument but %d were given.", argc - 1);
        fatal_error(argc_buffer);
    }

    const char* FILEPATH = argv[1];
    /* try to open file */
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {fatal_error("Cannot find or open file.");}



    const size_t FILE_SIZE = get_file_size(file);



    /* calculations for formatting */
    size_t header_length_per_line = COMPLETION_PERCENTAGE_LENGTH + SPACE_LENGTH + integer_length(file_size) + VERTICAL_LINE_LENGTH + SPACE_LENGTH;
    size_t payload_length_per_line = MAX_LINE_LENGTH - header_length_per_line;

    size_t formatted_hex_value_groups_per_line = (size_t)floor((double)payload_length_per_line/(double)FORMATTED_HEX_VALUES_GROUP_LENGTH);
    size_t formatted_hex_values_per_line = (size_t)floor((double)formatted_hex_value_groups_per_line*(double)FORMATTED_HEX_VALUES_GROUP_SIZE);

    size_t lines = (size_t)ceil((double)file_size/(double)formatted_hex_values_per_line);




    /* set up stdout full buffering */
    void* stdout_buffer = NULL;
    setvbuf(stdout, stdout_buffer, _IOFBF, MAX_LINE_LENGTH*(lines - 1));





    /* read and print content of file */
    unsigned int hex_value; // has to be int to be able to check for EOF
    for (size_t line = 0; line < lines; line++)
    {
        print_header(line, lines, formatted_hex_values_per_line);

        for (size_t _ = 0; _ < formatted_hex_value_groups_per_line; _++)
        {

            for (size_t _ = 0; _ < FORMATTED_HEX_VALUES_GROUP_SIZE && (hex_value = fgetc(file)) != EOF; _++) 
            {
                printf("%0*X ", HEX_VALUE_LENGTH, hex_value);
            }
            printf(" ");
            
        }       
        printf("\n");
    }


    fclose(file);

    
    return 0;   
}