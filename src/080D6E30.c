// func_080D6E30: 0x080D6E30-0x080D6EEC (188 bytes)
// Builds a BgAffineSet source from an object's two coordinate bytes and the
// scroll, scale and angle arguments, runs it through func_08141864 and copies
// the resulting matrix and offsets into the BG2 (bg == 2) or BG3 shadow
// registers of g_control_flags_03000940.
#include "ffta.h"
#include "control_flags.h"

struct BgAffineSrc {
    s32 texX;
    s32 texY;
    s16 scrX;
    s16 scrY;
    s16 sx;
    s16 sy;
    u16 alpha;
};

struct BgAffineDst {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 dx;
    s32 dy;
};

void func_08141864(const struct BgAffineSrc *src, struct BgAffineDst *dst, s32 count);

void func_080D6E30(const u8 *pos, u8 bg, s16 scrX, s16 scrY, s16 sx, s16 sy, u16 alpha)
{
    struct BgAffineSrc src;
    struct BgAffineDst dst;

    src.texX = pos[2] << 8;
    src.texY = pos[3] << 8;
    src.scrX = scrX;
    src.scrY = scrY;
    src.sx = sx;
    src.sy = sy;
    src.alpha = alpha;
    func_08141864(&src, &dst, 1);
    if (bg == 2) {
        g_control_flags_03000940.bg2pa = dst.pa;
        g_control_flags_03000940.bg2pb = dst.pb;
        g_control_flags_03000940.bg2pc = dst.pc;
        g_control_flags_03000940.bg2pd = dst.pd;
        g_control_flags_03000940.bg2x_l = dst.dx;
        g_control_flags_03000940.bg2x_h = dst.dx >> 16;
        g_control_flags_03000940.bg2y_l = dst.dy;
        g_control_flags_03000940.bg2y_h = dst.dy >> 16;
    } else {
        g_control_flags_03000940.bg3pa = dst.pa;
        g_control_flags_03000940.bg3pb = dst.pb;
        g_control_flags_03000940.bg3pc = dst.pc;
        g_control_flags_03000940.bg3pd = dst.pd;
        g_control_flags_03000940.bg3x_l = dst.dx;
        g_control_flags_03000940.bg3x_h = dst.dx >> 16;
        g_control_flags_03000940.bg3y_l = dst.dy;
        g_control_flags_03000940.bg3y_h = dst.dy >> 16;
    }
}
