#ifndef DATA_UNITS_H
#define DATA_UNITS_H

#include <stdlib.h>

/* 
Most struct members are defined as double to facilitate calculations,
but they are intended to store whole numbers.
*/
typedef struct data_unit
{
    size_t raw_unit_len;
    double raw_unit_padding;
    
    double unit_len;
    double unit_group_size;
    double unit_group_len;

} DataUnit;

#endif