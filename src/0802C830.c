#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 *data_0200F440;
extern BufferCopier data_0836D4BC[];
extern s32 func_081426B8(s32 value, s32 divisor);
extern s32 func_08142950(s32 value, s32 divisor);

/* Complete [0x0802C830, 0x0802C8C4): 148 bytes.
 * 70b5204a1268204bd618051c09040c14002c00da64421d48844200dd041c201c642115f131ff
 * 4101002906d0184871180368281c202215f1f3fc201c0a2115f123ff0a2116f16cf84101632c
 * 01dc002907d00f4a281c203071181368202215f1dffc201c0a2116f15bf84101084a281c4030
 * 71181368202215f1d2fc70bc01bc0047000040f400029c070000e7030000bcd43608
 */
void func_0802C830(void *destination, s16 value)
{
    u8 *digits = data_0200F440 + 0x79C;
    /* The u8 view of the void *destination that the matched siblings
     * src/0802BC7C.c, 0802BB70.c, 0802BD90.c and 0802BEB0.c take after
     * their digit base: the ROM forms data_0200F440 + 0x79C in r6
     * (0x0802C832-0x0802C838) before it copies r0 to r5 (0x0802C83A). */
    u8 *buffer = destination;
    s32 magnitude = value;
    u32 tile;

    if (magnitude < 0)
        magnitude = -magnitude;
    if (magnitude > 999)
        magnitude = 999;

    tile = func_081426B8(magnitude, 100) * 0x20;
    if (tile != 0)
        data_0836D4BC[0](buffer, digits + tile, 0x20);

    tile = func_08142950(func_081426B8(magnitude, 10), 10) * 0x20;
    if (magnitude > 99 || tile != 0)
        data_0836D4BC[0](buffer + 0x20, digits + tile, 0x20);

    tile = func_08142950(magnitude, 10) * 0x20;
    data_0836D4BC[0](buffer + 0x40, digits + tile, 0x20);
}
