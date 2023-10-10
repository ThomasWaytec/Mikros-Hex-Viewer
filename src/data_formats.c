#include <stdlib.h>

#include "char_lengths.h"
#include "data_formats.h"

const char SUPPORTED_DATA_FORMATS[] = {'h', 'b', 'd'};

/* hexadecimal */
DataFormat hex = {
    .raw_len = 2,
    .raw_padding = 2.0,

    .len = 2 + SPACE_LEN,              /* .raw_len + SPACE_LEN */
    .group_size = 4.0,
    .group_len = 3.0*4.0 + SPACE_LEN   /* .len*.group_size + SPACE_LEN */ 
};

/* binary */
DataFormat bin = {
    .raw_len = 8,
    .raw_padding = 8.0,

    .len = 8 + SPACE_LEN,              /* .raw_len + SPACE_LEN */
    .group_size = 1.0,
    .group_len = 9.0*1.0 + SPACE_LEN   /* .len*.group_size + SPACE_LEN */ 
};

/* decimal */
DataFormat dec = {
    .raw_len = 3,
    .raw_padding = 3.0,

    .len = 3 + SPACE_LEN,              /* .raw_len + SPACE_LEN */
    .group_size = 3.0,
    .group_len = 4.0*3.0 + SPACE_LEN   /* .len*.group_size + SPACE_LEN */ 
};