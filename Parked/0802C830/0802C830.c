#include "ffta.h"

extern u8 *data_0200F440;
extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);
extern s32 func_081426B8(s32 value, s32 divisor);
extern s32 func_08142950(s32 value, s32 divisor);

/* Target 0x0802C830..0x0802C8C4, 148 bytes:
 * 70b5204a1268204bd618051c09040c14002c00da64421d48844200dd041c201c642115f131ff
 * 4101002906d0184871180368281c202215f1f3fc201c0a2115f123ff0a2116f16cf84101632c
 * 01dc002907d00f4a281c203071181368202215f1dffc201c0a2116f15bf84101084a281c4030
 * 71181368202215f1d2fc70bc01bc0047000040f400029c070000e7030000bcd43608
 */
void func_0802C830(u8 *destination, s16 value)
{
    u8 *source = data_0200F440 + 0x79C;
    s32 magnitude = value;
    u32 offset;

    if (magnitude < 0)
        magnitude = -magnitude;
    if (magnitude > 999)
        magnitude = 999;

    offset = (u32)func_081426B8(magnitude, 100) << 5;
    if (offset != 0)
        data_0836D4BC(destination, source + offset, 32);

    offset = (u32)func_08142950(func_081426B8(magnitude, 10), 10) << 5;
    if (magnitude > 99 || offset != 0)
        data_0836D4BC(destination + 32, source + offset, 32);

    offset = (u32)func_08142950(magnitude, 10) << 5;
    data_0836D4BC(destination + 64, source + offset, 32);
}
