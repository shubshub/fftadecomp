#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xC6];
    u8 mode;
} MenuState080CC65C;

extern u8 func_080C8194(const void *object, u8 category);
extern void func_080C9574(u16 bitIndex, u16 enabled);

/* Complete target: [0x080CC65C, 0x080CC6F0), 148 bytes, 60 instructions. */
void func_080CC65C(MenuState080CC65C *menu)
{
    menu->mode = 0;
    menu->flags &= ~8;
    menu->flags &= ~0x10;

    if (func_080C8194(menu, 8))
        func_080C9574(0x38, 0);
    if (func_080C8194(menu, 0x5E))
        func_080C9574(0x46, 0);
    if (func_080C8194(menu, 4))
        func_080C9574(0x47, 0);
    if (func_080C8194(menu, 0xC))
        func_080C9574(0x48, 0);
    if (func_080C8194(menu, 9))
        func_080C9574(0x49, 0);
}
