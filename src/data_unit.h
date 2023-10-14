#ifndef DATA_UNIT_H
#define DATA_UNIT_H

/*
A data unit (data_unit_t) is a composite of one or many data formats (data_format_t).
It is a logical unit, an added layer of abstraction so the main file (mikros_hex_viewer.c)
can work more easily with multiple data formats.
*/

/* 
Most struct members are defined as double to facilitate calculations,
but they are intended to store whole numbers.
*/
typedef struct data_unit {

    data_format_t* data_formats;    /* the data formats the data unit is made up of */
    size_t data_formats_len;        /* the length of .data_formats */
    
    double len;                     /* the sum of all data_format.len in .data_formats */

    double group_size;              /* the number data units in one data unit group */
    char* group_sep;                /* separator for data unit groups when printed consecutively */
    double group_len;               /* how many characters a data unit group takes up in total */

    double groups_per_line;         /* number of data unit groups per line when printed */
    double per_line;                /* number of data units per line when printed */


} data_unit_t;

#endif