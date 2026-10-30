#include "ffta.h"

extern u16 data_03003860[];

/* Complete [0x0813FB68, 0x0813FB7C): 20 bytes, 7 reachable Thumb instructions.
 * 00040349c00b4018002101807047000060380003
 */
void func_0813FB68(u16 index)
{
    data_03003860[index] = 0;
}
