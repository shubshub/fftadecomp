#include "ffta.h"
#include "control_flags.h"

// Complete target [0x08135B40, 0x08135CFC): 444 bytes, 180 instructions
// and 18 literal words.

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u8 *destination;
} Display08135B40;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08135B40;

extern DmaRegisters08135B40 data_040000D4;
extern u16 data_03003860[];
extern u8 data_06008000[];
extern u8 data_0600E800[];
extern u8 data_0600F000[];
extern u8 data_0600F800[];
extern Display08135B40 data_03000E60;
extern Display08135B40 data_03000E80;
extern Display08135B40 data_030008B0;
extern Display08135B40 data_03000990;
extern void (*const g_callbacks_0836D4B8[])(void *, u32);

extern u8 func_08137B14(void);
extern void func_08141868(const void *source, void *destination, u32 control);
/* The ROM thunk at 0x0814224C branches to the callback in R2. */
extern void func_0814224C(void *destination, u32 size, void (*callback)(void *, u32));

void func_08135B40(void)
{
    void (*const *callbacks)(void *, u32);
    u16 fill;
    u32 zero;

    if (func_08137B14() == 2) {
        u16 *source = &fill;

        *source = 0;
        {
            // plausible: DMA3 MMIO requires volatile writes and control readback.
            volatile DmaRegisters08135B40 *dma = &data_040000D4;

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
            volatile DmaRegisters08135B40 *dma = &data_040000D4;

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
    g_control_flags_03000940.bg2cnt = 0x3F09;
    g_control_flags_03000940.bldcnt_lo = 0x42;
    g_control_flags_03000940.bldcnt_hi = 0x25;
    g_control_flags_03000940.winout_lo = 0x3F;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.bldalpha_lo = 0xB;
    g_control_flags_03000940.bldalpha_hi = 0xE;
    g_control_flags_03000940.bldy_lo = 0x10;
    g_control_flags_03000940.winin_lo = 0;
    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = 0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1v_lo = 0;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1040;

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

    callbacks = g_callbacks_0836D4B8;
    func_0814224C(data_03000E60.destination, 0x800, callbacks[0]);
    func_0814224C(data_03000E80.destination, 0x800, callbacks[0]);
    /* The third clear uses the prior BG3 destination. BG2 was configured above. */
    func_0814224C(data_03000990.destination, 0x800, callbacks[0]);
}
