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

/* most macros are defined as doubles for easier calculations further on */
#define PCT_SIGN_LEN 1.0        /* PCT = PERCENTAGE */
#define SPACE_LEN 1.0
#define NEW_LINE_LEN 1.0
#define VERTICAL_LINE_LEN 1.0
#define RAW_HEX_LEN 2           /* max. possible length of a byte represented in hexadecimal */
                                /* raw, as in they aren't formatted */
#define RAW_HEX_PADDING 2.0     
#define COMPLETION_PCT_LEN 4.0  /* PCT = PERCENTAGE*/

#define HEX_LEN (RAW_HEX_LEN + SPACE_LEN)                               
#define HEX_GROUP_SIZE 4.0                                  /* the number offormatted hex values in one group */
#define HEX_GROUP_LEN (HEX_LEN*HEX_GROUP_SIZE + SPACE_LEN)  /* how many characters a formatted hex group takes up */





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
const size_t get_file_size(FILE* file) {

    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);            
    fseek(file, 0, SEEK_SET);

    return FILE_SIZE;
}

void print_header(size_t current_line, double lines, double hex_per_line) {
        size_t completion_pct = (current_line + 1)/lines*100;
        size_t completion_pct_padding = COMPLETION_PCT_LEN - PCT_SIGN_LEN;

        size_t hex_printed = hex_per_line*(double)current_line;
        size_t hex_printed_padding = int_len(hex_per_line*lines);


        printf("%0*u%% %0*u| ", completion_pct_padding, completion_pct, hex_printed_padding, hex_printed);

}



int main(int argc, char* argv[]) {


    /* validate coommand-line arguments count */
    if ((argc - 1) != 1) {
        char* argc_buffer = calloc(sizeof(char), 54 + int_len(argc) + 1);
        sprintf(argc_buffer, "Program takes 1 command-line argument but %d were given.", argc - 1);
        fatal_error(argc_buffer);
    }

    const char* FILEPATH = argv[1];
    /* try to open file */
    FILE* file = fopen(FILEPATH, "rb");
    if (file == NULL) {fatal_error("Cannot find or open file.");}



    const size_t FILE_SIZE = get_file_size(file);


    /* defined as double for easier calculations */
    double header_len = COMPLETION_PCT_LEN + SPACE_LEN + int_len(FILE_SIZE) + VERTICAL_LINE_LEN + SPACE_LEN;
    double payload_len = MAX_LINE_LEN - header_len;
    
    double hex_groups_per_line = floor((payload_len - NEW_LINE_LEN)/HEX_GROUP_LEN);
    double hex_per_line = floor(hex_groups_per_line*HEX_GROUP_SIZE);

    size_t lines = (size_t)ceil((double)FILE_SIZE/hex_per_line);




    /* set up stdout full buffering */
    void* stdout_buffer = NULL;
    setvbuf(stdout, stdout_buffer, _IOFBF, INT_MAX);





    /* read and print content of file */
    unsigned int hex; // has to be int to be able to check for EOF
    for (size_t line = 0; line < lines; line++)
    {
        print_header(line, lines, hex_per_line);

        for (size_t _ = 0; _ < hex_groups_per_line; _++)
        {

            for (size_t _ = 0; _ < HEX_GROUP_SIZE && (hex = fgetc(file)) != EOF; _++) 
            {
                printf("%0*X ", RAW_HEX_LEN, hex);
            }
            printf(" ");
            
        }       
        printf("\n");
    }


    fclose(file);
    return 0;   
}