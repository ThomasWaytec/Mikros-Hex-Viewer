#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "char_len_constants.h"
#include "data_formats.h"


void print_hex(size_t byte);
void print_bin(size_t byte);
void print_dec(size_t byte);



/* hexadecimal */
const data_format_t hex = {
    .raw_len = 2,
    .raw_padding = 2,

    .len = 2.0 + SPACE_LEN,             /* .raw_len + SPACE_LEN */
    .group_size = 4.0,
    .group_len = 3.0*4.0 + SPACE_LEN,   /* .len*.group_size + SPACE_LEN */
    .print = print_hex,

    .exist = true,
};

void print_hex(size_t byte) {
    printf("%0*X ", hex.raw_padding, byte);
}




/* binary */
const data_format_t bin = {
    .raw_len = 8,
    .raw_padding = 8,

    .len = 8.0 + SPACE_LEN,             /* .raw_len + SPACE_LEN */
    .group_size = 1.0,
    .group_len = 9.0*1.0 + SPACE_LEN,   /* .len*.group_size + SPACE_LEN */
    .print = print_bin,

    .exist = true,
};

void print_bin(size_t byte) {
    for (size_t i = bin.raw_padding - 1; i + 1; i--) {
        printf("%d", (byte & (1 << i)) > 0);
    }
    printf(" ");
}




/* decimal */
const data_format_t dec = {
    .raw_len = 3,
    .raw_padding = 3,

    .len = 3.0 + SPACE_LEN,             /* .raw_len + SPACE_LEN */
    .group_size = 3.0,
    .group_len = 4.0*3.0 + SPACE_LEN,   /* .len*.group_size + SPACE_LEN */
    .print = print_dec,

    .exist = true,
};

void print_dec(size_t byte) {
    printf("%0*d ", dec.raw_padding, byte);
}

const char SUPPORTED_DATA_FORMATS[] = {HEXADECIMAL, BINARY, DECIMAL};
const data_format_t DATA_FORMATS_MAP[] = {[HEXADECIMAL] = hex, [BINARY] = bin, [DECIMAL] = dec};
