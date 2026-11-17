#include "ffta.h"
#include "control_flags.h"

// Complete target [0x0813BDD0, 0x0813BEEC): 284 bytes, 123 instructions
// and 8 literal words.

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters0813BDD0;

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    void *destination;
} Display0813BDD0;

typedef void (*BufferInitializer0813BDD0)(void *, u32);

extern DmaRegisters0813BDD0 data_040000D4;
extern u16 data_03003860[];
extern Display0813BDD0 data_03000E60;
extern u8 data_06008000[];
extern BufferInitializer0813BDD0 const g_callbacks_0836D4B8[];

extern void func_08141868(const void *source, void *destination, u32 control);

void func_0813BDD0(void)
{
    u16 zero;
    u32 fill;

    {
        u16 *source = &zero;

        *source = 0;
        {
            /* plausible: DMA3 MMIO requires volatile writes and control readback. */
            volatile DmaRegisters0813BDD0 *dma = &data_040000D4;
            dma->source = source;
            dma->destination = data_03003860;
            dma->control = 0x81000100;
            (void)dma->control;
        }
    }
    {
        u16 *source = &zero;

        *source = 0;
        {
            /* plausible: DMA3 MMIO requires volatile writes and control readback. */
            volatile DmaRegisters0813BDD0 *dma = &data_040000D4;
            dma->source = source;
            dma->destination = data_03003860 + 0x100;
            dma->control = 0x81000100;
            (void)dma->control;
        }
    }
    fill = 0;
    func_08141868(&fill, (void *)0x06000000, 0x01006000);

    g_control_flags_03000940.bg0hofs = 0;
    g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg0hofs;
    g_control_flags_03000940.bg0cnt = 0x3000;
    g_control_flags_03000940.bldcnt_lo = 0;
    g_control_flags_03000940.bldcnt_hi = 0;
    g_control_flags_03000940.winout_lo = 0;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.bldalpha_lo = 16;
    g_control_flags_03000940.bldalpha_hi = 0;
    g_control_flags_03000940.bldy_lo = 16;
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
    g_control_flags_03000940.display = 0x140;

    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = data_06008000;
    data_03000E60.vertical_offset = 0;
    data_03000E60.horizontal_offset = 0;
    data_03000E60.unknown_0d = 32;
    data_03000E60.unknown_0c = 32;

    g_callbacks_0836D4B8[0](data_06008000, 0x800);
}
