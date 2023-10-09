#ifndef DATA_UNITS_H
#define DATA_UNITS_H

#include <stdlib.h>

/* 
Most struct members are defined as double to facilitate calculations,
but they are intended to store whole numbers.
*/
typedef struct data_unit
{
    size_t raw_unit_len;        /* max. possible length of a byte represented in the given data representation */
    double raw_unit_padding;    /* raw, as in it isn't formatted */
    
    double unit_len;            /* the length of a formatted unit */
    double unit_group_size;     /* the number of formatted units in one unit group */
    double unit_group_len;      /* how many characters a formatted unit group takes up in total */

} DataUnit;

#endif