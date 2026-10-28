#include "ffta.h"

/* 0x08029F18..0x08029F7C: 100 bytes. */
struct Window08029F18 {
    u8 unknown_00[0x14];
    u16 *tilemap;
};

struct Resources08029F18 {
    u8 unknown_00[0x1F64];
    const u8 *data;
};

extern u16 data_02003CB0[];
extern struct Resources08029F18 g_state_02000000;
extern void func_08029DD4(u16 *buffer, u32 count, const u8 *source,
                         u16 attributes);
extern void func_08141570(s32 player, u16 sound);
extern void func_0814186C(const void *source, void *destination, u32 count);

void func_08029F18(u32 offset, struct Window08029F18 *window, u16 *buffer,
                   u16 x, u16 y)
{
    u16 *work = buffer;
    u16 *destination;
    s32 row;

    if (work == 0)
        work = data_02003CB0;
    row = (s16)y * 32 + 0x21;
    destination = window->tilemap + (row + (s16)x);
    func_08029DD4(work, 8, g_state_02000000.data + offset, 0xD000);
    func_08141570(1, 0x73);
    func_0814186C(work, destination, 8);
}
