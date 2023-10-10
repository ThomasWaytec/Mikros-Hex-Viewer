#ifndef DATA_UNIT_H
#define DATA_UNIT_H

#define DATA_FORMATS_LEN 8
/*
A data unit (data_unit_t) is a composite of one or many data formats (data_format_t).
It is a logical unit, an added layer of abstraction so the main file (mikros_hex_viewer.c)
can work more easily with multiple data formats.
*/

/* 
The struct members are defined as double to facilitate calculations,
but they are intended to store whole numbers.
*/
typedef struct data_unit {

    char data_formats[DATA_FORMATS_LEN];   /* the type of data formats the data unit is made up of */
    double len;             /* the sum of all the data formats' lengths in .data_formats */

    double group_size;      /* the number data units in one data unit group */
    double group_len;       /* how many characters a data unit group takes up in total */


} data_unit_t;

#endif