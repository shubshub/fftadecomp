#include "ffta.h"

typedef struct {
    s8 first;
    s8 second;
    s8 unknown_02;
    s8 third;
    s8 fourth;
    s8 fifth;
} Availability;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09[0x87];
    Availability *availability;
} Menu;

u8 func_080C9540(u32 flag);
u32 func_080D0AB0(u32 first, u32 second);
u16 func_080CE8A8(void);
u8 func_08050C74(u32 mode);
u8 func_08050CA4(u32 mode);
u32 func_08050CE8(Menu *menu, u32 mode);

/* Complete target: [0x080504BC, 0x080505BA), 254 bytes. */
u32 func_080504BC(Menu *menu)
{
    if (menu->mode != 1) {
        return 0;
    }

    if (func_080C9540(0x207)) {
        u8 old_third = menu->availability->third;
        u8 old_fourth = menu->availability->fourth;

        if (func_080D0AB0(0, 16) == 0) {
            menu->availability->first = 0;
        }
        if (func_080CE8A8() == 0) {
            menu->availability->second = 0;
        }
        if (func_08050C74(0) == 0) {
            menu->availability->third = 0;
        }
        if (func_08050CA4(0) == 0) {
            menu->availability->fourth = 0;
        }
        if (func_08050CE8(menu, 0) == 0) {
            menu->availability->fifth = 0;
        }

        return old_third != menu->availability->third ||
               old_fourth != menu->availability->fourth;
    } else {
        u8 old_third = menu->availability->third;

        if (func_080D0AB0(0, 16) == 0) {
            menu->availability->first = 0;
        }
        if (func_080CE8A8() == 0) {
            menu->availability->second = 0;
        }
        if (func_08050C74(0) == 0) {
            menu->availability->third = 0;
        }
        if (func_08050CE8(menu, 0) == 0) {
            menu->availability->fourth = 0;
        }

        return old_third != menu->availability->third;
    }
}
