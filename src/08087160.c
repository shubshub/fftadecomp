#include "control_flags.h"

typedef struct {
    u32 unknown_00;
    s32 x;
    s32 y;
    u8 width;
    u8 height;
    u8 unknown_0E[2];
    u8 *tiles;
    u16 *map;
} Layer08087160;

extern u16 data_03003860[];
extern u16 data_030027F0;
extern u16 data_03000EB0;
extern Layer08087160 data_03000E60;
extern Layer08087160 data_03000E80;
extern Layer08087160 data_030008B0;
extern Layer08087160 data_03000990;
extern u8 data_06008000[];
extern u16 data_06007000[];
extern u16 data_06006000[];
extern u16 data_06005800[];
extern u16 data_06005000[];
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete [0x08087160, 0x08087300), 416 bytes including the literal pool. */
void func_08087160(void)
{
    u16 bg_fill;
    u16 obj_fill;
    u16 *source;
    source = &bg_fill;
    *source = 0;
    func_0814186C(source, data_03003860, 0x01000100);
    source = &obj_fill;
    *source = 0;
    func_0814186C(source, data_03003860 + 256, 0x01000100);

    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg1vofs = 4;
    g_control_flags_03000940.bg0hofs = g_control_flags_03000940.bg1hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs =
        g_control_flags_03000940.bg3vofs = g_control_flags_03000940.bg3hofs = 0;
    g_control_flags_03000940.bg0cnt = 0xAE0B;
    g_control_flags_03000940.bg1cnt = 0xAC0A;
    g_control_flags_03000940.bg2cnt = 0x2B0A;
    g_control_flags_03000940.bg3cnt = 0x2A08;

    g_control_flags_03000940.bldcnt_lo = 0x44;
    g_control_flags_03000940.bldcnt_hi = 0x11;
    data_030027F0 = 0x1144;
    data_03000EB0 = 0x1144;
    g_control_flags_03000940.bldy_lo = 0;
    g_control_flags_03000940.bldalpha_lo = 11;
    g_control_flags_03000940.bldalpha_hi = 8;

    g_control_flags_03000940.win0h_hi = g_control_flags_03000940.win0h_lo =
        g_control_flags_03000940.win0v_hi = g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = g_control_flags_03000940.win1h_hi =
        g_control_flags_03000940.win1v_lo = g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1F40;
    g_control_flags_03000940.winout_lo = 0x3F;
    g_control_flags_03000940.winout_hi = 0;

    data_03000E60.tiles = data_06008000;
    data_03000E60.map = data_06007000;
    data_03000E60.x = data_03000E60.y = 0;
    data_03000E60.width = 64;
    data_03000E60.height = 32;
    data_03000E80.tiles = data_06008000;
    data_03000E80.map = data_06006000;
    data_03000E80.x = data_03000E80.y = 0;
    data_03000E80.width = 64;
    data_03000E80.height = 32;
    data_030008B0.tiles = data_06008000;
    data_030008B0.map = data_06005800;
    data_030008B0.x = data_030008B0.y = 0;
    data_030008B0.width = 32;
    data_030008B0.height = 32;
    data_03000990.tiles = data_06008000;
    data_03000990.map = data_06005000;
    data_03000990.x = data_03000990.y = 0;
    data_03000990.width = 32;
    data_03000990.height = 32;
}
