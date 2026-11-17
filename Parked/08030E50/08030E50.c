#include "control_flags.h"

// Complete target [0x08030E50, 0x08031060): 528 bytes, 228 instructions.
// Clears the palette buffer, resets the LCD register shadows, and points the
// four background records at their VRAM tiles and maps.

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    void *destination;
} Display08030E50;

typedef struct {
    u8 unknown_00[0x88];
    void *map_88;
    void *map_8c;
    void *map_90;
    void *map_94;
} State08030E50;

extern State08030E50 *g_state_03002810;
extern u16 data_03003860[];
extern Display08030E50 data_03000E60;
extern Display08030E50 data_03000E80;
extern Display08030E50 data_030008B0;
extern Display08030E50 data_03000990;
extern u8 data_06005000[];
extern u8 data_06006000[];
extern u8 data_06007000[];
extern u8 data_06007800[];
extern u8 data_06008000[];

extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08030E50(void)
{
    u16 clear;
    u16 *source;
    u16 clear_upper[1];

    source = &clear;
    *source = 0;
    func_0814186C(source, data_03003860, 0x01000100);
    clear_upper[0] = 0;
    func_0814186C(clear_upper, data_03003860 + 0x100, 0x01000100);

    g_control_flags_03000940.bg0hofs = 0;
    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg0hofs;
    g_control_flags_03000940.bg1hofs = 0;
    g_control_flags_03000940.bg1vofs = g_control_flags_03000940.bg1hofs;
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs;
    g_control_flags_03000940.bg3hofs = 0;
    g_control_flags_03000940.bg3vofs = g_control_flags_03000940.bg3hofs;
    g_control_flags_03000940.bg0cnt = 0xAA03;
    g_control_flags_03000940.bg1cnt = 0xAC02;
    g_control_flags_03000940.bg2cnt = 0x2E09;
    g_control_flags_03000940.bg3cnt = 0x2F08;

    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.winin_lo = g_control_flags_03000940.winin_hi;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win0v_hi = g_control_flags_03000940.win0v_lo;
    g_control_flags_03000940.win0h_lo = g_control_flags_03000940.win0v_hi;
    g_control_flags_03000940.win0h_hi = g_control_flags_03000940.win0h_lo;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.win1v_lo = g_control_flags_03000940.win1v_hi;
    g_control_flags_03000940.win1h_hi = g_control_flags_03000940.win1v_lo;
    g_control_flags_03000940.win1h_lo = g_control_flags_03000940.win1h_hi;

    g_control_flags_03000940.display = 0x1F40;
    g_control_flags_03000940.bldcnt_lo = 0x46;
    g_control_flags_03000940.bldcnt_hi = 0x13;
    g_control_flags_03000940.bldy_lo = 0;
    g_control_flags_03000940.bldalpha_lo = 13;
    g_control_flags_03000940.bldalpha_hi = 8;

    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.winin_lo = g_control_flags_03000940.winin_hi;
    g_control_flags_03000940.winout_lo = 0x3F;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win0h_lo = g_control_flags_03000940.win0v_lo;
    g_control_flags_03000940.win0v_hi = g_control_flags_03000940.win0h_lo;
    g_control_flags_03000940.win0h_hi = g_control_flags_03000940.win0v_hi;

    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = data_06005000;
    data_03000E60.vertical_offset = 0;
    data_03000E60.horizontal_offset = 0;
    data_03000E60.unknown_0c = 0x40;
    data_03000E60.unknown_0d = 0x20;

    data_03000E80.tiles = (u8 *)0x06000000;
    data_03000E80.destination = data_06006000;
    data_03000E80.vertical_offset = 0;
    data_03000E80.horizontal_offset = 0;
    data_03000E80.unknown_0c = 0x40;
    data_03000E80.unknown_0d = 0x20;

    data_030008B0.tiles = data_06008000;
    data_030008B0.destination = data_06007000;
    data_030008B0.vertical_offset = 0;
    data_030008B0.horizontal_offset = 0;
    data_030008B0.unknown_0c = 0x20;
    data_030008B0.unknown_0d = 0x20;

    data_03000990.tiles = data_06008000;
    data_03000990.destination = data_06007800;
    data_03000990.vertical_offset = 0;
    data_03000990.horizontal_offset = 0;
    data_03000990.unknown_0c = 0x20;
    data_03000990.unknown_0d = 0x20;

    g_state_03002810->map_8c = data_03000E60.destination;
    g_state_03002810->map_88 = data_03000E80.destination;
    g_state_03002810->map_94 = data_030008B0.destination;
    g_state_03002810->map_90 = data_03000990.destination;
}
