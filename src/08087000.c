#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} Character;

typedef struct {
    u8 unknown_0000[0x1d10];
    u8 window[1];
} DisplayState;

extern Character g_state_02000080[];
extern DisplayState *data_03002818;
extern u8 data_03000990[];
extern u8 data_030008B0[];

extern void func_0801174C(void *window, u8 x, u8 y, void *first,
                         void *second, s32 index, u32 flags,
                         u32 width, u32 height, u32 tile);
extern void func_08013210(Character *character, u32 flags, u32 tile);

/* 0x08087000..0x08087078: 120 bytes, 45 instructions. */
void func_08087000(u8 x, u8 y, u16 selection)
{
    Character *character = &g_state_02000080[selection];

    func_0801174C(data_03002818->window, x, y,
                  data_03000990, data_030008B0, -1, 0, 22, 6, 0x157);
    func_08013210(character, 0, 0x4300);
}
