#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813F22C, 0x0813F438): 524 bytes, 213 instructions
// and 17 literal words.

typedef struct {
    u32 unknown_00;
    u32 unknown_04;
    u32 unknown_08;
    u8 unknown_0C;
    u8 unknown_0D;
    u8 unknown_0E[2];
    void *tiles;
    void *map;
} Layer0813F22C;

typedef void (*BufferInitializer0813F22C)(void *destination, u32 size);

extern u8 *data_0200F3B0;
extern u16 data_03003860[0x200];
extern Layer0813F22C data_03000E60;
extern Layer0813F22C data_03000990;
extern Layer0813F22C data_030008B0;
extern u8 data_06008000[];
extern u8 data_06007000[];
extern u8 data_06004C00[];
extern u8 data_06005800[];
extern u8 data_06005000[];
extern BufferInitializer0813F22C const g_callbacks_0836D4B8[];

extern u8 func_080C9540(u16 flag);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_0813FB7C(void *destination, u8 color);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer0813F22C callback);

void func_0813F22C(void)
{
    u16 first;
    u16 second;
    u32 zero;
    BufferInitializer0813F22C const *callbacks;

    /* Both arms clear the two 0x100-entry halves of data_03003860 to 0.  The
     * ROM keeps the flag test (0x0813F236-0x0813F240) and both arms, which
     * differ only in the halfword slot that feeds each fill: sp+0 then sp+2
     * when the flag is clear (0x0813F244, 0x0813F256), sp+2 then sp+0 when
     * it is set (0x0813F276, 0x0813F286). */
    if (func_080C9540(0x44) == 0) {
        first = 0;
        func_0814186C(&first, &data_03003860[0], 0x01000100);
        second = 0;
        func_0814186C(&second, &data_03003860[0x100], 0x01000100);
    } else {
        second = 0;
        func_0814186C(&second, &data_03003860[0], 0x01000100);
        first = 0;
        func_0814186C(&first, &data_03003860[0x100], 0x01000100);
    }
    zero = 0;
    func_08141868(&zero, (void *)0x06000000, 0x01006000);

    g_control_flags_03000940.bg0hofs = 0;
    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg0hofs;
    g_control_flags_03000940.bg1hofs = 0;
    g_control_flags_03000940.bg1vofs = g_control_flags_03000940.bg1hofs;
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = g_control_flags_03000940.bg2hofs;
    g_control_flags_03000940.bg3hofs = 0;
    g_control_flags_03000940.bg3vofs = g_control_flags_03000940.bg3hofs;
    g_control_flags_03000940.bg0cnt = 0x8E8A;
    g_control_flags_03000940.bg3cnt = 0x0B01;
    g_control_flags_03000940.bg2cnt = 0x0A00;
    g_control_flags_03000940.bldcnt_lo = 0x40;
    g_control_flags_03000940.bldcnt_hi = 0x29;
    g_control_flags_03000940.bldalpha_lo = 0x10;
    g_control_flags_03000940.bldalpha_hi = 0;
    g_control_flags_03000940.bldy_lo = 0x10;
    g_control_flags_03000940.winout_lo = 0x3C;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.winin_lo = 0x37;
    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = 0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1v_lo = 0;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1940;

    data_03000E60.tiles = data_06008000;
    data_03000E60.map = data_06007000;
    data_03000E60.unknown_08 = 0;
    data_03000E60.unknown_04 = 0;
    data_03000E60.unknown_0C = 0x20;
    data_03000E60.unknown_0D = 0x40;
    data_03000990.tiles = data_06004C00;
    data_03000990.map = data_06005800;
    data_03000990.unknown_08 = 0;
    data_03000990.unknown_04 = 0;
    data_03000990.unknown_0D = 0x20;
    data_03000990.unknown_0C = 0x20;
    data_030008B0.tiles = (void *)0x06000000;
    data_030008B0.map = data_06005000;
    data_030008B0.unknown_08 = 0;
    data_030008B0.unknown_04 = 0;
    data_030008B0.unknown_0D = 0x20;
    data_030008B0.unknown_0C = 0x20;
    *(u16 *)(data_0200F3B0 + 0x8DD6) = 0;

    func_0813FB7C(data_06004C00, 1);
    callbacks = g_callbacks_0836D4B8;
    func_0814224C(data_03000E60.map, 0x800, callbacks[0]);
    func_0814224C(data_030008B0.map, 0x800, callbacks[0]);
    func_0814224C(data_03000990.map, 0x800, callbacks[0]);
}
