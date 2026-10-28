#include "ffta.h"

/* Complete [0x08142750, 0x0814278A): 58 bytes, 20 instructions. */
extern long long __fixunsdfdi(double value);

long long func_08142750(double value)
{
    if (value < 0)
        return -__fixunsdfdi(-value);
    return __fixunsdfdi(value);
}
