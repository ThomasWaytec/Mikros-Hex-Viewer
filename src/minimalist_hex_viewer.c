#include <stdio.h>


const char FILEPATH[] = "..\\test_files\\jpeg\\test_1.jpg";

int main(void) {


    FILE* file = fopen(FILEPATH, "r");



    char hex_value;
    do {
        hex_value = fgetc(file);
        printf("%c\n", hex_value);
        printf("%X", EOF);

    } while (hex_value != EOF);
    printf("Loop terminated!");

    
    
}