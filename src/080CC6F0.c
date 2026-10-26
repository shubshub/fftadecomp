#include "ffta.h"

/* 0x080CC6F0..0x080CC788: 152 bytes, 66 instructions. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xC6];
    u8 mode;
    u8 unknown_F1[0x11];
    u8 state;
    u8 substate;
} MenuState;

extern u8 func_080C8194(MenuState *menu, u32 condition);
extern void func_080C9574(u32 option, u32 enabled);

void func_080CC6F0(MenuState *menu, u8 mode)
{
    menu->mode = mode;
    menu->state = 0;
    menu->substate = 0;
    if (func_080C8194(menu, 8)) {
        func_080C9574(0x38, 1);
    }
    if (func_080C8194(menu, 0x5E)) {
        func_080C9574(0x46, 1);
    }
    if (func_080C8194(menu, 4)) {
        func_080C9574(0x47, 1);
    }
    if (func_080C8194(menu, 0xC)) {
        func_080C9574(0x48, 1);
    }
    if (func_080C8194(menu, 9)) {
        func_080C9574(0x49, 1);
    }
    menu->flags |= 8;
    menu->flags |= 0x10;
}
