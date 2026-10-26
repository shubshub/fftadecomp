#include "ffta.h"

typedef struct {
    u8 unknown_00[0xc08];
    void *display;
} DisplayState080354AC;

typedef struct {
    u8 unknown_00[0x108];
} Character080354AC;

extern DisplayState080354AC *g_state_03002810;
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern u8 data_08526CD8[][14];
extern Character080354AC g_state_02000080[];

void func_0801174C(void *display, u8 x, u8 y, void *first, void *second,
                   s32 index, u32 flags, u32 width, u32 height, u32 tile);
u8 func_080C8570(u8 first, u8 second, u32 field);
void func_08013108(u8 first, u8 second, u32 flags, u32 tile);
void func_08013210(Character080354AC *character, u32 flags, u32 tile);

void func_080354AC(u8 x, u8 y, u16 selection)
{
    func_0801174C(g_state_03002810->display, x, y,
                   data_03000990, data_030008B0, -1, 0, 0x16, 6, 0xcb);

    if (selection & 0x8000) {
        u8 first;
        u8 second;

        selection &= 0x7fff;
        if (selection > 0x7f) {
            const u8 *entry = data_08526CD8[selection];
            first = entry[0xb];
            second = entry[0xd];
        } else {
            u8 index = selection;
            first = func_080C8570(index, index, 9);
            second = func_080C8570(index, index, 0xb);
        }
        func_08013108(first, second, 0, 0x24c0);
    } else {
        func_08013210(&g_state_02000080[selection], 0, 0x24c0);
    }
}
