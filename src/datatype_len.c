#include <stdlib.h>
#include <math.h>

size_t size_t_len(size_t value) {
    if (value == 0) {return 1;}

    return floor(log10(abs(value))) + 1;
}

size_t double_len(double value) {
    if (value == 0) {return 1;}

    return floor(log10(abs(value))) + 1;
}
