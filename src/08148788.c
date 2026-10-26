#include "ffta.h"

/* Target: complete [0x08148788, 0x0814882E), 166 bytes, 78 instructions. */
extern u8 func_0801CC7C(u8, u8);
extern s16 func_0801CC38(u8, u8, u8);
extern u8 func_0801CD08(u8, u8);
extern void func_081491C0(void *, s16, s16, u32, u32, u32, u32, u32);

void func_08148788(void *context, u16 x, u16 y)
{
    if ((s16)x >= 0 && (s16)y >= 0) {
        u8 column = x;
        u8 row = y;

        if (!func_0801CC7C(column, row)) {
            func_081491C0(context, (s16)x, (s16)y, 0, 0, 1, 0, 0);
        } else {
            u8 height = func_0801CC38(column, row, 8);
            u8 flags = func_0801CD08(column, row);

            if (flags & 1)
                func_081491C0(context, (s16)x, (s16)y, 0, 0, 1, 0, 0);
            else
                func_081491C0(context, (s16)x, (s16)y, 1, height, 0, 0, 0);
        }
    }
}
