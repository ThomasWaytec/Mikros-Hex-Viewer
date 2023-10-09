#include <stdlib.h>

#include "char_lengths.h"
#include "data_units.h"

/* binary */
DataUnit bin = {
    .raw_unit_len = 8,
    .raw_unit_padding = 8.0,

    .unit_len = 8 + SPACE_LEN,              /* .raw_unit_len + SPACE_LEN */
    .unit_group_size = 1.0,
    .unit_group_len = 9.0*1.0 + SPACE_LEN   /* .unit_len*.unit_group_size + SPACE_LEN */ 
};

/* hexadecimal */
DataUnit hex = {
    .raw_unit_len = 2,
    .raw_unit_padding = 2.0,

    .unit_len = 2 + SPACE_LEN,              /* .raw_unit_len + SPACE_LEN */
    .unit_group_size = 4.0,
    .unit_group_len = 3.0*4.0 + SPACE_LEN   /* .unit_len*.unit_group_size + SPACE_LEN */ 
};

/* decimal */
DataUnit dec = {
    .raw_unit_len = 3,
    .raw_unit_padding = 3.0,

    .unit_len = 3 + SPACE_LEN,              /* .raw_unit_len + SPACE_LEN */
    .unit_group_size = 3.0,
    .unit_group_len = 4.0*3.0 + SPACE_LEN   /* .unit_len*.unit_group_size + SPACE_LEN */ 
};