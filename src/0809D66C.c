#include "ffta.h"

void func_0809D66C(s8 direction, s8 *x, s8 *z)
{
    switch (direction) {
    case 0:
        *x = 0;
        *z = 1;
        break;
    case 1:
        *x = -1;
        *z = 0;
        break;
    case 2:
        *x = 0;
        *z = -1;
        break;
    case 3:
        *x = 1;
        *z = 0;
        break;
    default:
        *x = 0;
        *z = 0;
        break;
    }
}
