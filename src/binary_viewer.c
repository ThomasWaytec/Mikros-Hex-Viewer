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

#define BYTE 8

#define MAX_LINE_LENGTH get_terminal_width()

#define PERCENTAGE_SIGN_LENGTH 1
#define SPACE_LENGTH 1
#define VERTICAL_LINE_LENGTH 1
#define HEX_VALUE_LENGTH 2 /* max. possible length of a byte represented in hexadecimal */
#define DECIMAL_VALUE_LENGTH 3 /* max. possible length of a byte represented in decimal */
#define HEX_VALUE_PADDING 2
#define COMPLETION_PERCENTAGE_LENGTH 4

#define FORMATTED_HEX_VALUE_LENGTH (HEX_VALUE_LENGTH + SPACE_LENGTH)
#define FORMATTED_HEX_VALUES_GROUP_SIZE 4
#define FORMATTED_HEX_VALUES_GROUP_LENGTH (FORMATTED_HEX_VALUE_LENGTH*FORMATTED_HEX_VALUES_GROUP_SIZE + SPACE_LENGTH)



void fatal_error(const char* message)
{
    fprintf(stderr,"\nError: %s\n", message);
    exit(EXIT_FAILURE);
}

size_t integer_length(size_t number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;
}


void print_binary(unsigned int value) {
    printf("0b"); /* print binary prefix */

    for (size_t i = BYTE - 1; i + 1; i--) {
        printf("%d", (value & (1 << i)) > 0);
    }

}

void print_hex(unsigned int value) {
    printf("0x"); /* print hex prefix */
    
    printf("%0*X", HEX_VALUE_LENGTH, value);
}


void print_decimal(unsigned int value) {
    printf("0d"); /* print decimal prefix */

    printf("%0*d", DECIMAL_VALUE_LENGTH, value);
}

void print_header(const size_t FILE_SIZE, size_t hex_values_printed) {
        size_t completion_percentage = (size_t)(double)(hex_values_printed + 1)/(double)FILE_SIZE*100;
        size_t completion_percentage_padding = COMPLETION_PERCENTAGE_LENGTH - PERCENTAGE_SIGN_LENGTH;

        size_t hex_values_printed_padding = integer_length(FILE_SIZE);

        printf("%0*u%% %0*u| ", completion_percentage_padding, completion_percentage, hex_values_printed_padding, hex_values_printed);

}



int main(int argc, char* argv[]) {


    /* validate coommand-line arguments count */
    /*
    if ((argc - 1) != 1) {
        char* argc_buffer = calloc(sizeof(char), 54 + integer_length(argc) + 1);
        sprintf(argc_buffer, "Program takes 1 command-line argument but %d were given.", argc - 1);
        fatal_error(argc_buffer);
    }
    */

    const char* FILEPATH = "test_files/jpeg/test_3.jpg";
    //const char* FILEPATH = argv[1];
    /* try to open file */
    FILE* file = fopen(FILEPATH, "rb");
    //if (file == NULL) {fatal_error("Cannot find or open file.");}



    /* get file size */
    fseek(file, 0, SEEK_END);          
    const size_t FILE_SIZE = ftell(file);
    fseek(file, 0, SEEK_SET);
    



    /* calculations for formatting */
    size_t header_length_per_line = COMPLETION_PERCENTAGE_LENGTH + SPACE_LENGTH + integer_length(FILE_SIZE) + VERTICAL_LINE_LENGTH + SPACE_LENGTH;
    size_t payload_length_per_line = MAX_LINE_LENGTH - header_length_per_line;

    size_t formatted_hex_value_groups_per_line = (size_t)floor((double)payload_length_per_line/(double)FORMATTED_HEX_VALUES_GROUP_LENGTH);
    size_t formatted_hex_values_per_line = (size_t)floor((double)formatted_hex_value_groups_per_line*(double)FORMATTED_HEX_VALUES_GROUP_SIZE);

    size_t lines = (size_t)ceil((double)FILE_SIZE/(double)formatted_hex_values_per_line);




    /* set up stdout full buffering */
    //void* stdout_buffer = NULL;
    //setvbuf(stdout, stdout_buffer, _IOFBF, MAX_LINE_LENGTH*(lines - 1));




    /*
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
    */



    size_t hex_values_printed = 0;
    unsigned int hex_value;
    while ((hex_value = fgetc(file)) != EOF) {
        print_header(FILE_SIZE, hex_values_printed);
        print_binary(hex_value);
        printf("\n");
        print_hex(hex_value);
        printf("   ");
        print_decimal(hex_value);
        printf("\n");

        hex_values_printed++;
    }
    
    return 0;   
}   
