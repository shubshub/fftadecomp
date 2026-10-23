/* 0x0800A1E4 - 44 bytes
 * Target: 30b5 051c 0c1c 6078 a178 0902 0843 bff0a5f9 0006 0028 06d0 e178 2079 0002 0143 6888 0918 6980 30bc 01bc 0047
 */
#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 field_02;
} Context0800A1E4;

u8 func_080C9540(u16 bitIndex);

void func_0800A1E4(Context0800A1E4 *context, const u8 *instruction)
{
    if (func_080C9540(instruction[1] | (instruction[2] << 8)))
        context->field_02 += instruction[3] | (instruction[4] << 8);
}
