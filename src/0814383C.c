#include "dp_bit.h"

double func_0814383C(int value)
{
    fp_number_type number;

    number.class = 3;
    number.sign = value < 0;
    if (value == 0) {
        number.class = 2;
    } else {
        number.normal_exp = 60;
        if (number.sign) {
            if (value == (-2147483647 - 1))
                return -2147483648.0;
            number.fraction.ll = -value;
        } else {
            number.fraction.ll = value;
        }
        while (number.fraction.ll < ((fractype)1 << 60)) {
            number.fraction.ll <<= 1;
            number.normal_exp--;
        }
    }
    return func_08142BE8(&number);
}
