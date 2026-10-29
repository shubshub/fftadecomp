#include "ffta.h"

/* Complete [0x0804FD60, 0x0804FDF4): 148 bytes, 63 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *row;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[8];
    u8 stride;
} Menu0804FD60;

extern u16 func_080161A0(u8, u8, u8);
extern void *func_0804CA8C(void);
extern void func_08000BAC(void *, const u16 *, void *, u16, u16, u16, u16);

void func_0804FD60(Menu0804FD60 *menu)
{
    u16 *row = menu->row;
    u16 *source;
    s32 i;

    row += menu->width * 2;
    for (i = 1; i < menu->width - 1; i++)
        row[i] = 0xc050;
    row[0] = 0xc051;
    row[menu->width - 1] = 0xc451;
    source = menu->row + func_080161A0(0, 2, menu->stride);
    row = menu->destination + func_080161A0(0, 2, 32);
    func_08000BAC(func_0804CA8C(), source, row, menu->width,
                  1, menu->width * 2, 64);
}
