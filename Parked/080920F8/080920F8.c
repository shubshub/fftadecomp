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

/* The same pair writer is present at 08092084 and inlined in 080901A8. */
static inline void set_alpha(u8 *base, s16 index, u8 first, u8 second)
{
    u32 offset = index * 2;
    base[offset] = first;
    ++base;
    base[offset] = second;
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

    for (i = 0; i < 160; ++i)
        set_alpha((u8 *)context->scanlines, i, 0, 16);

    func_08000D48(context->scanlines->channel, context->scanlines,
                  (void *)0x04000052, 0x20400001);
    context->mode = 0;
    return context;
}
