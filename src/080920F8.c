/* func_080920F8 - complete [0x080920F8, 0x08092180): 136 bytes, 56
 * instructions, including the four-word literal pool.
 *
 * Builds a scanline alpha-blend context: an 84-byte context cleared through
 * the buffer initializer, and a 328-byte table of 160 (EVA, EVB) byte pairs
 * whose byte at +324 selects the DMA channel that streams it to BLDALPHA. */

#include "control_flags.h"
#include "oam_lists.h"

typedef struct {
    u8 alpha[160][2];
    u8 unknown_140[4];
    u8 channel;
    u8 unknown_145[3];
} BlendScanlines;

typedef struct {
    BlendScanlines *scanlines;
    s16 center;
    s16 limit;
    s16 position;
    u16 unknown_0A;
    u16 mode;
    u8 unknown_0E[0x46];
} ScanlineContext;

extern void *func_08022840(u32 size);
extern void func_08000D48(u32 channel, const void *source, void *destination,
                         u32 control);

/* An inlined copy of func_08092084 (src/08092084.c), as src/080901A8.c
 * writes it: the out-of-line copy, 0x74 bytes before this function,
 * stores its third argument first. */
static inline void inlined_08092084(u8 *base, s16 index, u8 lo, u8 hi) {
    u32 off = index * 2;
    base[off] = lo;
    base++;
    base[off] = hi;
}

ScanlineContext *func_080920F8(s32 channel)
{
    ScanlineContext *context;
    BlendScanlines *scanlines;
    s32 i;

    context = func_08022840(sizeof(*context));
    g_callbacks_0836D4B8[0](context, sizeof(*context));
    scanlines = func_08022840(sizeof(*scanlines));
    scanlines->channel = channel;
    context->scanlines = scanlines;
    g_control_flags_03000940.bldalpha_lo = 0;
    g_control_flags_03000940.bldalpha_hi = 16;

    /* The ROM loads the loop-invariant 16 (0x08092138) before the 0
     * (0x0809213A), so EVB is set before EVA.  Literal arguments are
     * copied in parameter order, which loads the 0 first. */
    for (i = 0; i < 160; ++i) {
        u8 evb = 16;
        u8 eva = 0;

        inlined_08092084((u8 *)context->scanlines, i, eva, evb);
    }

    func_08000D48(context->scanlines->channel, context->scanlines,
                  (void *)0x04000052, 0x20400001);
    context->mode = 0;
    return context;
}
