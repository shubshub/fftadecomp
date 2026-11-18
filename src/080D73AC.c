#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 unknown_00[2];
    u8 x;
    u8 y;
} Position;

typedef struct AffineParameters080032F8 {
    s16 pa, pb, pc, pd;
    s32 x, y;
} AffineParameters080032F8;

extern const u32 data_083954C0[];
extern const u8 data_0600C000[];
extern u16 func_08003A74(u32 packed);
extern u16 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern u16 func_080035A8(u8 layer);
extern void func_080032F8(const AffineParameters080032F8 *transform, u32 layer);

/* 080D73AC..080D7468: 188 bytes. */
void func_080D73AC(const Position *position, u8 bank, u8 layer,
                   s16 x, s16 y, u8 wrap)
{
    u16 control;
    s32 dx, dy;
    AffineParameters080032F8 transform;

    control = func_08003A74(data_083954C0[bank]) | 0x4000 |
              func_08003A80((u32)data_0600C000) | 0x80;
    if (wrap)
        control |= 0x2000;
    func_080034B8(control, layer);
    {
        u32 mask = func_080035A8(layer);
        u16 flags = g_control_flags_03000940.display;
        flags |= mask;
        g_control_flags_03000940.display = flags;
    }
    dx = (position->x - x) * 256;
    dy = (position->y - y) * 256;
    transform.pa = 0x100;
    transform.pb = 0;
    transform.pc = 0;
    transform.pd = 0x100;
    transform.x = dx;
    transform.y = dy;
    func_080032F8(&transform, layer);
}
