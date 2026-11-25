#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813F438, 0x0813F604): 460 bytes, 190 instructions
// and 16 literal words.

/* The display records as src/0813FD78.c, src/0813FEC8.c and src/08140010.c
 * declare them. */
typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u16 *destination;
} Display0813F438;

typedef void (*BufferInitializer0813F438)(void *destination, u32 size);

extern u16 data_03003860[];
extern Display0813F438 data_03000E60;
extern Display0813F438 data_03000E80;
extern Display0813F438 data_030008B0;
extern Display0813F438 data_03000990;
extern u8 data_06002400[];
extern u16 data_06007000[];
extern u16 data_06006000[];
extern u16 data_06005800[];
extern u16 data_06005000[];
extern BufferInitializer0813F438 g_callbacks_0836D4B8[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0813FB68(u16 index);
extern void func_0813FB7C(void *destination, u8 color);

void func_0813F438(void)
{
    /* CpuFill16(0, ..., 0x200) of both halves of data_03003860: the SDK's
     * vu16 temporary, spelled through a pointer until fftadecomp-kit#164, in
     * the text of src/0807B858.c.  src/08087160.c and src/0804C8C4.c make the
     * same two fills.  Each fill has its own halfword (sp+0, sp+2) and takes
     * its address before the zero (mov r0, sp at 0x0813F440 and 0x0813F452). */
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, data_03003860, 0x01000100);
    }
    {
        u16 zero;
        u16 *p = &zero;
        *p = 0;
        func_0814186C(p, data_03003860 + 0x100, 0x01000100);
    }

    g_control_flags_03000940.bg0hofs = 0;
    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg0hofs;
    g_control_flags_03000940.bg1hofs = 0;
    g_control_flags_03000940.bg1vofs = g_control_flags_03000940.bg1hofs;
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs;
    g_control_flags_03000940.bg3hofs = 0;
    g_control_flags_03000940.bg3vofs = g_control_flags_03000940.bg3hofs;
    g_control_flags_03000940.bg0cnt = 0x0E03;
    g_control_flags_03000940.bg1cnt = 0x0C03;
    g_control_flags_03000940.bg2cnt = 0x0A00;
    g_control_flags_03000940.bg3cnt = 0x0B00;
    g_control_flags_03000940.bldcnt_lo = 0x40;
    g_control_flags_03000940.bldcnt_hi = 0x31;
    g_control_flags_03000940.bldalpha_lo = 0x10;
    g_control_flags_03000940.bldalpha_hi = 0;
    g_control_flags_03000940.bldy_lo = 0x10;
    g_control_flags_03000940.winout_lo = 0x38;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.winin_lo = 0x31;
    g_control_flags_03000940.winin_hi = 0x32;
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = 0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1v_lo = 0;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1B40;

    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = data_06007000;
    data_03000E60.vertical_offset = 0;
    data_03000E60.horizontal_offset = 0;
    data_03000E60.unknown_0d = 0x20;
    data_03000E60.unknown_0c = 0x20;

    data_03000E80.tiles = data_06002400;
    data_03000E80.destination = data_06006000;
    data_03000E80.vertical_offset = 0;
    data_03000E80.horizontal_offset = 0;
    data_03000E80.unknown_0d = 0x20;
    data_03000E80.unknown_0c = 0x20;

    data_030008B0.tiles = data_06002400;
    data_030008B0.destination = data_06005000;
    data_030008B0.vertical_offset = 0;
    data_030008B0.horizontal_offset = 0;
    data_030008B0.unknown_0d = 0x20;
    data_030008B0.unknown_0c = 0x20;

    data_03000990.tiles = (u8 *)0x06004C00;
    data_03000990.destination = data_06005800;
    data_03000990.vertical_offset = 0;
    data_03000990.horizontal_offset = 0;
    data_03000990.unknown_0d = 0x20;
    data_03000990.unknown_0c = 0x20;

    func_0813FB68(255);
    func_0813FB7C((u8 *)0x06004C00, 15);

    /* Called through the table, as in src/0813FD78.c.  The table is not
     * const: the ROM loads the entry again for each call (0x0813F59C,
     * 0x0813F5A4, 0x0813F5AE). */
    g_callbacks_0836D4B8[0](data_03000E60.destination, 0x800);
    g_callbacks_0836D4B8[0](data_03000E80.destination, 0x800);
    g_callbacks_0836D4B8[0](data_03000990.destination, 0x800);
}
