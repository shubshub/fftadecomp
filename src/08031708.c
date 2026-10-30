/* Target bytes (12):
 * 01 49 08 70 70 47 00 00 a4 27 00 03
 */
#include "ffta.h"

extern u8 data_030027A4;

void func_08031708(u8 value)
{
    data_030027A4 = value;
}
