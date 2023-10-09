#include <stdlib.h>

#include "char_lengths.h"
#include "data_units.h"


int main(void) 
{
    /* binary */
    extern DataUnit bin;
    bin.raw_unit_len = 8;
    bin.raw_unit_padding = 8.0;

    bin.unit_len = bin.raw_unit_len + SPACE_LEN;
    bin.unit_group_size = 1.0;
    bin.unit_group_len = bin.unit_len*bin.unit_group_size + SPACE_LEN;


    /* hexadecimal */
    extern DataUnit hex;
    hex.raw_unit_len = 2;
    hex.raw_unit_padding = 2.0;

    hex.unit_len = binary.raw_unit_len + SPACE_LEN;
    hex.unit_group_size = 4.0;
    hex.unit_group_len = binary.unit_len*binary.unit_group_size + SPACE_LEN;


    /* decimal */
    extern DataUnit dec;
    dec.raw_unit_len = 3;
    dec.raw_unit_padding = 3.0;

    dec.unit_len = binary.raw_unit_len + SPACE_LEN;
    dec.unit_group_size = 3.0;
    dec.unit_group_len = binary.unit_len*binary.unit_group_size + SPACE_LEN;
    
}
