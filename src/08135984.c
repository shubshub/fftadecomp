#include "ffta.h"
#include "control_flags.h"

// Complete target [0x08135984, 0x08135B40): 444 bytes, 178 instructions
// and 19 literal words.

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u8 *destination;
} Display08135984;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08135984;

extern DmaRegisters08135984 data_040000D4;
extern u16 data_03003860[];
extern u8 data_06008000[];
extern u8 data_0600E800[];
extern u8 data_0600F000[];
extern u8 data_0600F800[];
extern Display08135984 data_03000E60;
extern Display08135984 data_03000E80;
extern Display08135984 data_030008B0;
extern Display08135984 data_03000990;
extern void (*g_callbacks_0836D4B8[])(void *, u32);

extern u8 func_08137B14(void);
extern void func_08135D38(void);
extern void func_08141868(const void *source, void *destination, u32 control);

void func_08135984(void)
{
    u16 fill;
    u32 zero;

    /* Each arm fills both halves of data_03003860 with its own value, in the
     * text of src/08135B40.c, which has the same bytes here.  The ROM keeps
     * the start of each arm (mov r0, sp at 0x08135994 and 0x0813599A; the
     * 0x7FFF goes through r1 into r4 at 0x0813599C-0x0813599E) and shares
     * the rest from 0x081359A0.  With the value chosen first and one pair
     * of fills, the 0x7FFF is loaded straight into r4. */
    if (func_08137B14() == 2) {
        u16 *source = &fill;

        *source = 0;
        {
            // plausible: DMA3 MMIO requires volatile writes and control readback.
            volatile DmaRegisters08135984 *dma = &data_040000D4;

            dma->source = source;
            dma->destination = data_03003860;
            dma->control = 0x81000100;
            (void)dma->control;

            fill = 0;
            dma->source = source;
            dma->destination = data_03003860 + 0x100;
            dma->control = 0x81000100;
            (void)dma->control;
        }
    } else {
        u16 *source = &fill;

        *source = 0x7FFF;
        {
            // plausible: DMA3 MMIO requires volatile writes and control readback.
            volatile DmaRegisters08135984 *dma = &data_040000D4;

            dma->source = source;
            dma->destination = data_03003860;
            dma->control = 0x81000100;
            (void)dma->control;

            fill = 0x7FFF;
            dma->source = source;
            dma->destination = data_03003860 + 0x100;
            dma->control = 0x81000100;
            (void)dma->control;
        }
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
    g_control_flags_03000940.bg0cnt = 0x3D83;
    g_control_flags_03000940.bg1cnt = 0x3E0A;
    g_control_flags_03000940.bg2cnt = 0x3F08;
    g_control_flags_03000940.bldcnt_lo = 0x42;
    g_control_flags_03000940.bldcnt_hi = 3;
    g_control_flags_03000940.winout_lo = 0x2F;
    g_control_flags_03000940.winout_hi = 0;

    /* func_08135D38 stores 7 and 0xC to bldalpha (0x0300098C, 0x0300098D),
     * the two fields src/08135B40.c sets here itself. */
    func_08135D38();

    g_control_flags_03000940.bldy_lo = 0x10;
    g_control_flags_03000940.winin_lo = 0x3F;
    g_control_flags_03000940.winin_hi = 0x3F;
    g_control_flags_03000940.win0h_hi = 0x40;
    g_control_flags_03000940.win0h_lo = 0xB0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0xA0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1h_lo = 0xF0;
    g_control_flags_03000940.win1v_hi = 0x48;
    g_control_flags_03000940.win1v_lo = 0x86;
    g_control_flags_03000940.display = 0xF740;

    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = data_0600E800;
    data_03000E60.vertical_offset = 0;
    data_03000E60.horizontal_offset = 0;
    data_03000E60.unknown_0d = 0x20;
    data_03000E60.unknown_0c = 0x20;

    data_03000E80.tiles = data_06008000;
    data_03000E80.destination = data_0600F000;
    data_03000E80.vertical_offset = 0;
    data_03000E80.horizontal_offset = 0;
    data_03000E80.unknown_0d = 0x20;
    data_03000E80.unknown_0c = 0x20;

    data_030008B0.tiles = data_06008000;
    data_030008B0.destination = data_0600F800;
    data_030008B0.vertical_offset = 0;
    data_030008B0.horizontal_offset = 0;
    data_030008B0.unknown_0d = 0x20;
    data_030008B0.unknown_0c = 0x20;

    /* Called through the table, as src/0813FD78.c clears its maps.  The
     * table is not const: the ROM loads the entry again for each call
     * (0x08135ACE, 0x08135AD8, 0x08135AE4). */
    g_callbacks_0836D4B8[0](data_03000E60.destination, 0x800);
    g_callbacks_0836D4B8[0](data_03000E80.destination, 0x800);
    /* The third clear uses the prior BG3 destination. BG2 was configured above. */
    g_callbacks_0836D4B8[0](data_03000990.destination, 0x800);
}
