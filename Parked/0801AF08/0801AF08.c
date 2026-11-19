#include "ffta.h"

/* func_0801AF08 - complete [0x0801AF08, 0x0801B5D4): 1740 bytes, 826 instructions.
 * Target:
 * f0b557464e464546e0b48bb0019002910392049314980006000e059000200790
 * 019a118d48420004030c0893002802dd0124079412e0074d281c019a12898018
 * 08180004030c0893002805dd0224079404e0000000feffff002508950198418d
 * 48420004040c002804dd042007990143079114e0084a101c019b5b89c0180818
 * 0004040c002809dd0820079d05432806000e079003e0000000feffff00240898
 * 00040a90079900295fd003f049fb000600282ad0059a002a1ad0019bd98bda88
 * 6846018009490860029d4d6052088120000602438a6088688868802212060028
 * 13da886810400028fbd10ee0b00000040198c18bc28868460180520880204004
 * 02436846029926f12dfc03f021fb000600282ad0059900291ad0019ad18bd288
 * 6846018009490860039b4b6052088120000602438a6088688868802212060028
 * 13da886810400028fbd10ee0b0000004019de98bea8868460180520880204004
 * 02436846039926f1fdfb0a990814019a1389984200dd9fe22104081452899042
 * 00dd99e20a9ce0140004000c0890c8140004040c2025aa46d20890460198018d
 * 0804c0140004020c019d688d0004c0140004000c069000250020099080204000
 * 834200d0c2e003200799084000280dd053460899581a0004000c82460120079b
 * 1840002802d000224804050c0c200799084000280bd04346181b0004000c8046
 * 04200140002902d00020069009940699880110180004000c8146099a90012818
 * 0004070c03f08cfa0006002840d0059b002b27d04c466000049d43190298c119
 * 0022424534d20e4c80252d06ac4656462e4323606160a660a068a06865462840
 * 80334031551c002805d080221206a06810400028fbd12804020c4245e9d317e0
 * b000000449464800049a8518029bdc190026059840450bd2281c211c524626f1
 * 61fb80354034701c0004060c4645f3d303f04efa0006002800d1f8e105990029
 * 2cd04a465000139bc218039ce1190023434500d3ebe1104c80252d06a9464f46
 * 5046074322606160a760a068a0684d462840161c803640315d1c002805d08023
 * 1b06a06818400028fbd1321c2804030c4345e7d3cbe10000b000000449464800
 * 139a8518039bdc1900260598404500d3bde1281c211c524626f114fb80354034
 * 701c0004060c4645f3d3b0e1202290460c20079b184000280ad0101b0004000c
 * 804604201840002802d0002006900994202292460804c0140004020c089b1804
 * 01140a901f2905dd0220079c2040002800d1b9e00120079b1840002809d00022
 * 5446089d601b0004000c82460a98050c0de00220079b1840002808d0202906dd
 * 081c20385446201a0004000c82460699880110180004000c8146099a90016900
 * 40180004070c03f0abf90006002843d0059b002b2ad04c46600004994518029a
 * d1190023434537d20f4a80242406a44656462643156051609660906890686446
 * 204080350c1c40340133002805d080210906906808400028fbd1211c1804030c
 * 4345e7d318e00000b00000044d46680004994518029ad4190026059b43450bd2
 * 281c211c524626f17dfa80354034701c0004060c4645f3d303f06af900060028
 * 42d0059c002c29d04d46680013994218039bd9190024444536d20f4b80273f06
 * 3e1c55462e431a6059609e60986898683840151c803540310134002805d08022
 * 1206986810400028fbd12a1c2004040c4445e8d318e00000b000000449464800
 * 139a8518039bdc190026059840450bd2281c211c524626f135fa80354034701c
 * 0004060c4645f3d320218a46019a108d0004c01420300004020c00250a9b1914
 * 1f2905dd0120079c2040002800d1bee00220079b1840002806d054460899601a
 * 0004000c824614e00120079b0340002b0fd0202909dd002220395446601a0004
 * 000c824609040d0c03e02020401a0004020c0699880110180004000c8146099a
 * 90016900401880231b01c0180004070c03f0d6f80006002840d0059c002c27d0
 * 4d46680004994318029ad1190022424534d20e4c80252d06ac4656462e432360
 * 6160a660a068a0686546284080334031551c002805d080221206a06810400028
 * fbd12804020c4245e9d317e0b000000449464800049a8518029bdc1900260598
 * 40450bd2281c211c524626f1abf980354034701c0004060c4645f3d303f098f8
 * 0006002843d0059900292bd04a465000139bc218039ce1190023434537d2104c
 * 80252d06a9464f465046074322606160a760a068a0684d462840151c80354031
 * 5e1c002805d080231b06a06818400028fbd12a1c3004030c4345e7d317e00000
 * b000000449464800139a8618039bdd19002444450bd2301c291c524626f162f9
 * 80364035601c0004040c4445f3d3019ca18d05480840a0850bb038bc9846a146
 * aa46f0bc01bc0047feff0000
 *
 * Redraws the two BG tile maps for the scroll position in the state.  When
 * the view runs past an edge of the map (bit 0 left, 1 right, 2 top,
 * 3 bottom), both screen blocks are first filled with the fill tile.  The
 * visible window of each 64-tile-wide map buffer is then copied to its
 * screen block a row at a time, by DMA0 or by BIOS CpuSet as use_dma says,
 * for each layer that func_0801E648 / func_0801E658 report enabled.  A map
 * 256 pixels wide is one copy; a wider one is two, the columns from 32 on
 * going to the second screen block, 0x800 bytes further on.  Bit 0 of the
 * state flags is cleared at the end.
 */

typedef struct {
    u8 unknown_00[6];
    u16 screen_size;
    u16 width;
    u16 height;
    u8 unknown_0C[0x12];
    u16 fill_tile;
    u8 unknown_20[8];
    s16 x;
    s16 y;
    u16 flags;
} State0801AF08;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters0801AF08;

extern DmaRegisters0801AF08 data_040000B0;
extern u8 func_0801E648(void);
extern u8 func_0801E658(void);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* One DMA0 transfer and its completion wait, the register sequence of
 * src/080012BC.c's DMA0_COPY32; the ROM has it eight times (0x0801AFCC,
 * 0x0801B02C and the six row loops). */
#define DMA0_TRANSFER(src, dest, cnt)                                        \
    {                                                                        \
        /* plausible: DMA0 MMIO requires word writes and control readback. */ \
        volatile DmaRegisters0801AF08 *dma = &data_040000B0;                 \
        dma->source = (src);                                                 \
        dma->destination = (dest);                                           \
        dma->control = (cnt);                                                \
        (void)dma->control;                                                  \
    }                                                                        \
    {                                                                        \
        /* plausible: each test reads the current DMA0 enable bit. */        \
        volatile DmaRegisters0801AF08 *dma = &data_040000B0;                 \
        while (dma->control & 0x80000000)                                    \
            ;                                                                \
    }

/* Fills size bytes with one tile number.  The fill helpers are inline
 * functions: each call loads both arguments, the tile and the size, before
 * the tile is stored to the stack (0x0801AFC4-0x0801AFCA, 0x0801AFFA-0x0801B000
 * and the two calls for the second layer). */
static inline void dma_fill16(u16 value, void *destination, u16 size)
{
    u16 fill = value;

    DMA0_TRANSFER(&fill, destination, 0x81000000 | (size / 2));
}

static inline void cpu_fill16(u16 value, void *destination, u16 size)
{
    u16 fill = value;

    func_0814186C(&fill, destination, 0x01000000 | (size / 2));
}

/* Copies height rows of width tiles from a 64-tile-wide map buffer to a
 * 32-tile-wide screen block, the row loop of src/08020BA0.c's copy_rows.
 * The ROM has six copies of each loop. */
static inline void dma_copy_rows(const u16 *source, u8 *destination, u16 width, u16 height)
{
    u16 i;

    for (i = 0; i < height; i++) {
        DMA0_TRANSFER(source, destination, 0x80000000 | width);
        source += 64;
        destination += 64;
    }
}

static inline void cpu_copy_rows(const u16 *source, u8 *destination, u16 width, u16 height)
{
    u16 i;

    for (i = 0; i < height; i++) {
        func_0814186C(source, destination, width);
        source += 64;
        destination += 64;
    }
}

#define COPY_ROWS(source, destination)                      \
    {                                                       \
        if (use_dma)                                        \
            dma_copy_rows(source, destination, cols, rows); \
        else                                                \
            cpu_copy_rows(source, destination, cols, rows); \
    }

#define FILL(destination)                                                       \
    {                                                                           \
        if (use_dma)                                                            \
            dma_fill16(state->fill_tile, destination, state->screen_size);     \
        else                                                                    \
            cpu_fill16(state->fill_tile, destination, state->screen_size);     \
    }

void func_0801AF08(State0801AF08 *state, u8 *first, u8 *second, u16 *buffer,
                   u16 *secondary_buffer, u8 use_dma)
{
    u16 src_x;
    u16 src_y;
    u8 edges = 0;
    s16 dx;
    s16 dy;
    u16 cols;
    u16 rows;
    u16 dst_x;
    u16 dst_y;
    u16 src;
    u16 dst;

    dx = -state->x;
    if (dx > 0)
        edges |= 1;
    else {
        dx = state->x + (state->width - 0x200);
        if (dx > 0)
            edges |= 2;
        else
            dx = 0;
    }
    dy = -state->y;
    if (dy > 0)
        edges |= 4;
    else {
        dy = state->y + (state->height - 0x200);
        if (dy > 0)
            edges |= 8;
        else
            dy = 0;
    }

    if (edges) {
        if (func_0801E648())
            FILL(first);
        if (func_0801E658())
            FILL(second);
    }

    if (dx > state->width)
        return;
    if (dy > state->height)
        return;

    dx = dx >> 3;
    dy = dy >> 3;
    cols = 32;
    rows = state->height >> 3;
    src_x = state->x >> 3;
    src_y = state->y >> 3;
    dst_x = 0;
    dst_y = 0;

    if (state->width == 256) {
        if (edges & 3) {
            cols -= dx;
            if (edges & 1) {
                src_x = 0;
                dst_x = dx * 2;
            }
        }
        if (edges & 12) {
            rows -= dy;
            if (edges & 4) {
                src_y = 0;
                dst_y = dy;
            }
        }
        src = src_x + src_y * 64;
        dst = dst_x + dst_y * 64;
        if (func_0801E648())
            COPY_ROWS(buffer + src, first + dst);
        if (func_0801E658())
            COPY_ROWS(secondary_buffer + src, second + dst);
    } else {
        rows = 32;
        if (edges & 12) {
            rows -= dy;
            if (edges & 4) {
                src_y = 0;
                dst_y = dy;
            }
        }

        cols = 32;
        src_x = state->x >> 3;
        if (dx < 32 || (edges & 2)) {
            if (edges & 1) {
                src_x = 0;
                cols -= dx;
                dst_x = dx;
            } else if (edges & 2) {
                if (dx > 32)
                    cols -= dx - 32;
            }
            src = src_x + src_y * 64;
            dst = dst_y * 64 + dst_x * 2;
            if (func_0801E648())
                COPY_ROWS(buffer + src, first + dst);
            if (func_0801E658())
                COPY_ROWS(secondary_buffer + src, second + dst);
        }

        cols = 32;
        src_x = (state->x >> 3) + 32;
        dst_x = 0;
        if (dx < 32 || (edges & 1)) {
            if (edges & 2) {
                cols -= dx;
            } else if (edges & 1) {
                if (dx > 32) {
                    src_x = 0;
                    cols -= dx - 32;
                    dst_x = dx - 32;
                } else {
                    src_x = 32 - dx;
                }
            }
            src = src_x + src_y * 64;
            dst = dst_y * 64 + dst_x * 2 + 0x800;
            if (func_0801E648())
                COPY_ROWS(buffer + src, first + dst);
            if (func_0801E658())
                COPY_ROWS(secondary_buffer + src, second + dst);
        }
    }
    state->flags &= ~1;
}
