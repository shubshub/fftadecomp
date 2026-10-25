/* 0x0800A1BC - 20 bytes
 * Target: 00b5 4878 8a78 1202 1043 c978 bff0d4f9 01bc 0047
 */
#include "ffta.h"

void func_080C9574(u16 bitIndex, u16 enabled);

void func_0800A1BC(void *context, const u8 *instruction)
{
    func_080C9574(instruction[1] | (instruction[2] << 8), instruction[3]);
}
