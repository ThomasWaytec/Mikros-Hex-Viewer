#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LINE_LENGTH 160
#define COMPLETION_PERCENTAGE_LENGTH 4
#define SPACE_LENGTH 1
#define VERTICAL_LINE_LENGTH 1
#define HEX_VALUE_LENGTH 2
#define HEX_VALUE_PADDING 2
#define FORMATTED_HEX_VALUE_LENGTH (HEX_VALUE_LENGTH + SPACE_LENGTH)

const char FILEPATH[] = "test_files\\jpeg\\test_1.jpg";

size_t integer_length(size_t number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;
}

void print_header(size_t line, size_t lines, size_t formatted_hex_values_per_line) {
        size_t completion_percentage = (size_t)round((double)line/(double)lines*100);
        size_t completion_percentage_padding = COMPLETION_PERCENTAGE_LENGTH - 1;

        size_t no_of_formatted_hex_values_printed = (size_t)(double)formatted_hex_values_per_line*(double)line;
        size_t no_of_formatted_hex_values_printed_padding = integer_length((double)formatted_hex_values_per_line*(double)(lines));

        printf("%0*u%% %0*u| ", completion_percentage_padding, completion_percentage, no_of_formatted_hex_values_printed_padding, no_of_formatted_hex_values_printed);

}

int main(void) {


    FILE* file = fopen(FILEPATH, "rb");

    if (file == NULL) {printf("cant open file");}

    /* get file size */
    fseek(file, 0, SEEK_END);          
    size_t file_size = ftell(file);            
    rewind(file);



    size_t header_length_per_line = COMPLETION_PERCENTAGE_LENGTH + SPACE_LENGTH + integer_length(file_size) + VERTICAL_LINE_LENGTH + SPACE_LENGTH;
    size_t payload_length_per_line = MAX_LINE_LENGTH - header_length_per_line;
    size_t formatted_hex_values_per_line = (size_t)floor((double)payload_length_per_line/(double)FORMATTED_HEX_VALUE_LENGTH);
    size_t lines = (size_t)ceil((double)file_size/(double)formatted_hex_values_per_line);

    /* set up stdout full buffering */
    //char* stdout_buffer = calloc(sizeof(char), formatted_hex_values_per_line*FORMATTED_HEX_VALUE_LENGTH + header_length_per_line*lines);
    //setvbuf(stdout, stdout_buffer, _IOFBF, file_size);


    /* read and print content of file */
    unsigned int hex_value; // has to be int to be able to check for EOF
    for (size_t line = 0; line < lines; line++) {
        
        print_header(line, lines, formatted_hex_values_per_line);

        for (size_t i = 0; i < formatted_hex_values_per_line && (hex_value = fgetc(file)) != EOF; i++)
        {
            printf("%0*X ", HEX_VALUE_PADDING, hex_value);
        }
        
        printf("\n");
    }
    
    
    fclose(file);
    
    
    return 0;   
}