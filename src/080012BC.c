// func_080012BC: 0x080012BC-0x080014C8, 524 bytes, 229 instructions
// (including the sixteen-word literal pool at 0x08001488).
//
// Builds OAM from the sprite lists that are not being written this frame
// (index data_03000028 ^ 1 and data_03002F58 ^ 1): hides all 128 entries,
// DMA0-copies the four entry lists into OAM back to back, never past entry
// 128 (the second list leaves room for all of the third), then writes the
// affine parameters of every matrix whose flag is set.
#include "oam_lists.h"

/* DMA0 SAD, DAD and CNT. */
typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters;

extern DmaRegisters data_040000B0;

/* A 32-bit incrementing DMA0 copy of size bytes and its completion wait, the
 * register sequence of src/08000718.c; the ROM repeats it four times
 * (0x08001312, 0x08001386, 0x080013D2, 0x08001420). */
#define DMA0_COPY32(src, dest, size)                                        \
    {                                                                       \
        /* plausible: DMA0 MMIO requires word writes and control readback. */ \
        volatile DmaRegisters *dma = &data_040000B0;                        \
        dma->source = (src);                                                \
        dma->destination = (dest);                                          \
        dma->control = 0x84000000 | (size) / 4;                             \
        (void)dma->control;                                                 \
    }                                                                       \
    {                                                                       \
        /* plausible: each test reads the current DMA0 enable bit. */       \
        volatile DmaRegisters *dma = &data_040000B0;                        \
        while (dma->control & 0x80000000)                                   \
            ;                                                               \
    }

void func_080012BC(void)
{
    u16 *oam = (u16 *)0x07000000;
    s32 total = 0;
    s32 count;
    s32 limit;
    u32 size;
    u64 *source;
    u8 buffer;
    u8 other;
    AffineMatrix *matrix;
    u8 *used;
    s32 i;

    HideEntries((u64 *)oam, 0x80);

    buffer = data_03000028 ^ 1;
    other = data_03002F58 ^ 1;

    source = data_03002C58[buffer];
    count = data_03002C50[buffer];
    if (count > 0) {
        size = count * sizeof(u64);
        DMA0_COPY32(source, oam, size);
        oam = (u16 *)((u8 *)oam + size);
        total += count;
    }

    source = data_03002F68[other];
    count = data_03002F60[other];
    limit = 0x80 - total - data_03000020[buffer];
    if (count > limit)
        count = limit;
    if (count > 0) {
        size = count * sizeof(u64);
        DMA0_COPY32(source, oam, size);
        oam = (u16 *)((u8 *)oam + size);
        total += count;
    }

    source = data_03000030[buffer];
    count = data_03000020[buffer];
    limit = 0x80 - total;
    if (count > limit)
        count = limit;
    if (count > 0) {
        size = count * sizeof(u64);
        DMA0_COPY32(source, oam, size);
        oam = (u16 *)((u8 *)oam + size);
        total += count;
    }

    source = data_03003170[other];
    count = data_03003168[other];
    limit = 0x80 - total;
    if (count > limit)
        count = limit;
    if (count > 0) {
        size = count * sizeof(u64);
        DMA0_COPY32(source, oam, size);
        oam = (u16 *)((u8 *)oam + size);
        total += count;
    }

    /* Matrix i is the fourth halfword of OAM entries 4i to 4i+3, as in
     * src/08003454.c. */
    oam = (u16 *)0x07000006;
    matrix = data_030032B0[buffer];
    used = data_03003270[buffer];
    for (i = 0; i < 32; i++) {
        if (used[i]) {
            oam[0] = matrix->pa;
            oam[4] = matrix->pb;
            oam[8] = matrix->pc;
            oam[12] = matrix->pd;
        }
        matrix++;
        oam += 16;
    }
}
