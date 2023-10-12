#include <stdio.h>
#include <stdlib.h>

const size_t get_file_size(FILE* file) {

    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);            
    fseek(file, 0, SEEK_SET);

    return FILE_SIZE;
}
