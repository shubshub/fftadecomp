#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 width;
    u8 height;
    u8 *tiles;
    void *destination;
} Display08137CC4;

typedef struct {
    u8 unknown_00[0x08];
    void *destination_e80;
    void *destination_e60;
    void *destination_990;
    void *destination_8b0;
} Screens08137CC4;

extern u16 data_03003860[];
extern Display08137CC4 data_03000E60;
extern Display08137CC4 data_03000E80;
extern Display08137CC4 data_030008B0;
extern Display08137CC4 data_03000990;
extern Screens08137CC4 *data_030027D8;
extern u8 data_06008000[];
extern u8 data_06006800[];
extern u8 data_06006000[];
extern u8 data_06005800[];
extern u8 data_06005000[];
extern void func_0814186C(const void *source, void *destination, u32 control);

// Complete target: [0x08137CC4, 0x08137EC4), 512 bytes.
void func_08137CC4(void)
{
    u16 first;
    u16 second;
    u16 *p = &first;

    *p = 0;
    func_0814186C(p, data_03003860, 0x01000100);
    p = &second;
    *p = 0;
    func_0814186C(p, data_03003860 + 0x100, 0x01000100);

    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg0hofs = 0;
    g_control_flags_03000940.bg1vofs = g_control_flags_03000940.bg1hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg3vofs = g_control_flags_03000940.bg3hofs = 0;
    g_control_flags_03000940.bg0cnt = 0xAD0B;
    g_control_flags_03000940.bg1cnt = 0xAC09;
    g_control_flags_03000940.bg2cnt = 0x2B0A;
    g_control_flags_03000940.bg3cnt = 0x2A08;
    g_control_flags_03000940.winin_lo = g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.win0h_hi = g_control_flags_03000940.win0h_lo =
        g_control_flags_03000940.win0v_hi = g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = g_control_flags_03000940.win1h_hi =
        g_control_flags_03000940.win1v_lo = g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1F40;
    g_control_flags_03000940.bldcnt_lo = 0x44;
    g_control_flags_03000940.bldcnt_hi = 0x13;
    g_control_flags_03000940.bldy_lo = 0;
    g_control_flags_03000940.bldalpha_lo = 13;
    g_control_flags_03000940.bldalpha_hi = 8;
    g_control_flags_03000940.winin_lo = g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.winout_lo = 0x3F;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.win0h_hi = g_control_flags_03000940.win0v_hi =
        g_control_flags_03000940.win0h_lo = g_control_flags_03000940.win0v_lo = 0;

    data_03000E60.tiles = data_06008000;
    data_03000E60.destination = data_06006800;
    data_03000E60.vertical_offset = 0;
    data_03000E60.horizontal_offset = 0;
    data_03000E60.width = 32;
    data_03000E60.height = 32;
    data_03000E80.tiles = data_06008000;
    data_03000E80.destination = data_06006000;
    data_03000E80.vertical_offset = 0;
    data_03000E80.horizontal_offset = 0;
    data_03000E80.width = 32;
    data_03000E80.height = 32;
    data_030008B0.tiles = data_06008000;
    data_030008B0.destination = data_06005800;
    data_030008B0.vertical_offset = 0;
    data_030008B0.horizontal_offset = 0;
    data_030008B0.width = 32;
    data_030008B0.height = 32;
    data_03000990.tiles = data_06008000;
    data_03000990.destination = data_06005000;
    data_03000990.vertical_offset = 0;
    data_03000990.horizontal_offset = 0;
    data_03000990.width = 32;
    data_03000990.height = 32;

    data_030027D8->destination_e60 = data_03000E60.destination;
    data_030027D8->destination_e80 = data_03000E80.destination;
    data_030027D8->destination_8b0 = data_030008B0.destination;
    data_030027D8->destination_990 = data_03000990.destination;
}
