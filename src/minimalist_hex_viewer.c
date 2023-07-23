#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAX_LINE_LENGTH 160

#define PERCENTAGE_SIGN_LENGTH 1
#define SPACE_LENGTH 1
#define VERTICAL_LINE_LENGTH 1
#define HEX_VALUE_LENGTH 2
#define HEX_VALUE_PADDING 2
#define COMPLETION_PERCENTAGE_LENGTH 4

#define FORMATTED_HEX_VALUE_LENGTH (HEX_VALUE_LENGTH + SPACE_LENGTH)
#define FORMATTED_HEX_VALUES_GROUP_SIZE 4
#define FORMATTED_HEX_VALUES_GROUP_LENGTH (FORMATTED_HEX_VALUE_LENGTH*FORMATTED_HEX_VALUES_GROUP_SIZE + SPACE_LENGTH)

#define HCONSOLE GetStdHandle(STD_OUTPUT_HANDLE)



void fatal_error(const char* message)
{
    fprintf(stderr,"\nError: %s\n", message);
    exit(EXIT_FAILURE);
}

size_t integer_length(size_t number) {
    if (number == 0) {return 1;}

    return floor(log10(abs(number))) + 1;
}

void print_header(size_t line, size_t lines, size_t formatted_hex_values_per_line) {
        size_t completion_percentage = (size_t)(double)(line + 1)/(double)lines*100;
        size_t completion_percentage_padding = COMPLETION_PERCENTAGE_LENGTH - PERCENTAGE_SIGN_LENGTH;

        size_t no_of_formatted_hex_values_printed = (size_t)(double)formatted_hex_values_per_line*(double)line;
        size_t no_of_formatted_hex_values_printed_padding = integer_length((double)formatted_hex_values_per_line*(double)(lines));

        printf("%0*u%% %0*u| ", completion_percentage_padding, completion_percentage, no_of_formatted_hex_values_printed_padding, no_of_formatted_hex_values_printed);

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



    /* get file size */
    fseek(file, 0, SEEK_END);          
    size_t file_size = ftell(file);            
    rewind(file);




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