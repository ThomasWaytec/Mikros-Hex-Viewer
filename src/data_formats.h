#ifndef DATA_FORMATS_H
#define DATA_FORMATS_H

#include <stdlib.h>
#include <stdbool.h>

#define HEXADECIMAL 'x'
#define BINARY 'b'
#define DECIMAL 'd'
#define CHARACTER 'c'

/* 
Most struct members are defined as double to facilitate calculations,
but they are intended to store whole numbers.
*/
typedef struct data_format
{
    size_t raw_len;         /* max. possible length of a byte represented in the given data format/representation */
    size_t raw_padding;     /* raw, as in it isn't styled/formatted */
    
    double len;             /* the length (in characters) of a styled data format */
    double group_size;      /* the number of styled data formats in one group */
    double group_len;       /* how many characters a styled data format group takes up in total */

    void (*print)(size_t);  /* the associated print function for this data format */

    bool exist;             /* to check whether the object exists when looked up from a table. 
                               Should always be set to true
                            */


} data_format_t;


#endif