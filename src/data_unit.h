#ifndef DATA_UNIT_H
#define DATA_UNIT_h

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
    double len;

    double group_len;       /**/
    double group_size;      /* the combined group_size of all data formats*/
    char data_formats[8];   /* the type of data formats the data unit is made of */


} data_unit_t;

#endif