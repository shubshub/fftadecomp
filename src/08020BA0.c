#include "ffta.h"

/* func_08020BA0 - complete [0x08020BA0, 0x08020DA0): 512 bytes, 242 instructions.
 * Target:
 *   f0b557464e464546e0b485b00006000e00900020019000210291894600231549
 *   2c205843043009680d1828785a1c0392002800d1d5e06878011c009ca14200d0
 *   cfe0a879002800d1cbe06889002800d12889071c012907d1281c253000780190
 *   281c2630007802902889b84204d8071c14e00000d4f1000201290fd1019e7400
 *   381c211c049320f123fe0290381c211c20f120fe381a0004070c049baa89d019
 *   298988420ddd881a0004070c6878012807d101984100381c049320f109fe0290
 *   049b6878002807d0012823d04946c9198a460133039362e0286ae9690c4a1060
 *   5160b803000c842109060843906090689068802109064c46e419a24601330393
 *   00284cda906808400028fbd147e00000d4000004019e029908062a6a9446ea69
 *   000e804600244846c01982460133039344451fd221497000814680231b063343
 *   66460e604a608b6088688868802636063040161c80360134002805d080221206
 *   886810400028fbd1cc44321c2004040c4445e5d3a889c019298988420fd1faf7
 *   b3fd000600280ad12c1c2434201cfff727fd0006002802d0201cfff75bfd5246
 *   1004000c8146a88938180021a8810004000c2c89a04203d1a97112e0d4000004
 *   6878002802d0012803d007e0e869c01903e0029ef101e8694018e861286ac019
 *   286203990806030e032b00d817e7484605b038bc9846a146aa46f0bc02bc0847
 *
 * Runs the queued transfers of the slots of one kind and returns the number
 * of bytes moved.  A slot moves at most chunk_size bytes a call, or all of
 * size when chunk_size is 0, and never more than what is left of size.
 * Kind 0 is one 32-bit DMA3 copy of the amount.  Kind 1 copies whole rows of
 * width halfwords with 16-bit DMA3, the destination advancing 128 bytes a
 * row; the row count is dimensions[1], or the BIOS quotient of the amount and
 * the row size when the amount was cut short.  When a kind 1 slot reaches its
 * size, func_080207F4 gets its window if func_0801B888 returns 0 and
 * func_08020780 accepts the window.
 */
typedef struct {
    u8 layer;
    u8 dimensions[2];
    u8 x;
    u8 y;
} MapWindow;

typedef struct {
    u8 active;
    u8 kind;
    u8 unknown_02[4];
    u8 queued;
    u8 unknown_07;
    u16 size;
    u16 chunk_size;
    u16 elapsed;
    u8 unknown_0E[0xE];
    u8 *current_destination;
    const u8 *current_source;
    /* The record func_08020780 and func_080207F4 take (0x08020D28); agbcc
     * rounds its five bytes to eight, which ends the slot at 0x2C. */
    MapWindow window;
} AnimationSlot;

typedef struct {
    u16 tick;
    u16 unknown_02;
    AnimationSlot slots[4];
} AnimationState;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08020BA0;

extern AnimationState *g_state_0200F1D4;
extern DmaRegisters08020BA0 data_040000D4;
extern s32 func_08141870(s32 numerator, s32 denominator);
extern s32 func_08141874(s32 numerator, s32 denominator);
extern u8 func_0801B888(void);
extern u8 func_08020780(const MapWindow *window);
extern void func_080207F4(MapWindow *window);

/* Copies `rows` rows of `width` halfwords with DMA3, the source advancing by
 * the row and the destination by 128 bytes (kind 1, 0x08020CB4..0x08020D12).
 * The ROM has no out-of-line copy of it.  func_080207F4 expands the same row
 * loop twice (0x080209AA, 0x08020A14) with the same parameter order and u16
 * width and rows, for DMA0 and other strides. */
static inline void copy_rows(const u8 *source, u8 *destination, u16 width, u16 rows)
{
    u16 row;

    for (row = 0; row < rows; row++)
    {
        /* plausible: DMA3 MMIO requires word writes, control readback and completion polling. */
        volatile DmaRegisters08020BA0 *dma = &data_040000D4;
        dma->source = source;
        dma->destination = destination;
        dma->control = 0x80000000 | width;
        (void)dma->control;
        while (dma->control & 0x80000000)
            ;
        source += width * 2;
        destination += 128;
    }
}

u16 func_08020BA0(u8 kind)
{
    u32 width = 0;
    u32 rows = 0;
    u16 transferred = 0;
    u8 index;

    for (index = 0; index < 4; index++)
    {
        AnimationSlot *slot = &g_state_0200F1D4->slots[index];
        u16 amount;

        if (!slot->active || slot->kind != kind || !slot->queued)
            continue;

        amount = slot->chunk_size ? slot->chunk_size : slot->size;

        if (slot->kind == 1)
        {
            width = slot->window.dimensions[0];
            rows = slot->window.dimensions[1];
        }

        if (slot->size <= amount)
            amount = slot->size;
        else if (slot->kind == 1)
        {
            rows = func_08141870(amount, width * 2);
            amount -= func_08141874(amount, width * 2);
        }

        if (slot->elapsed + amount > slot->size)
        {
            amount = slot->size - slot->elapsed;
            if (slot->kind == 1)
                rows = func_08141870(amount, width * 2);
        }

        switch (slot->kind)
        {
        case 0:
        {
            const u8 *source = slot->current_source;
            u8 *destination = slot->current_destination;
            /* plausible: DMA3 MMIO requires word writes, control readback and completion polling. */
            volatile DmaRegisters08020BA0 *dma = &data_040000D4;
            dma->source = source;
            dma->destination = destination;
            dma->control = 0x84000000 | (amount / 4);
            (void)dma->control;
            while (dma->control & 0x80000000)
                ;
            break;
        }
        case 1:
            copy_rows(slot->current_source, slot->current_destination, width, (u8)rows);
            if (slot->elapsed + amount == slot->size &&
                !func_0801B888() && func_08020780(&slot->window))
                func_080207F4(&slot->window);
            break;
        }

        transferred += amount;
        slot->elapsed += amount;
        if (slot->elapsed == slot->size)
            slot->queued = 0;
        else
        {
            switch (slot->kind)
            {
            case 0:
                slot->current_destination += amount;
                break;
            case 1:
                slot->current_destination += rows * 128;
                break;
            }
            slot->current_source += amount;
        }
    }
    return transferred;
}
