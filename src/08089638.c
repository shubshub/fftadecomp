#include "ffta.h"

void func_08089638(u16 *destination, u16 value, u16 width)
{
    s32 column;

    for (column = 0; column < width; column++, destination++) {
        destination[0] = value;
        destination[width] = value;
    }
}
