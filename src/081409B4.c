#include "control_flags.h"

typedef struct AffineSource081409B4 {
    s32 texture_x;
    s32 texture_y;
    s16 screen_x;
    s16 screen_y;
    s16 scale_x;
    s16 scale_y;
    u16 angle;
} AffineSource081409B4;

typedef struct AffineParameters081409B4 {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineParameters081409B4;

extern void func_08141864(const AffineSource081409B4 *source, AffineParameters081409B4 *destination, s32 count);

// Complete target [0x081409B4, 0x08140A20): 108 bytes, 54 instructions.
void func_081409B4(s16 texture_x, s16 texture_y, s16 screen_x, s16 screen_y, s16 scale_x, s16 scale_y, u8 angle)
{
    AffineSource081409B4 source;
    AffineParameters081409B4 parameters;

    source.texture_x = texture_x << 8;
    source.texture_y = texture_y << 8;
    source.screen_x = screen_x;
    source.screen_y = screen_y;
    source.scale_x = scale_x;
    source.scale_y = scale_y;
    source.angle = angle << 8;
    func_08141864(&source, &parameters, 1);
    g_control_flags_03000940.bg2pa = parameters.pa;
    g_control_flags_03000940.bg2pb = parameters.pb;
    g_control_flags_03000940.bg2pc = parameters.pc;
    g_control_flags_03000940.bg2pd = parameters.pd;
    g_control_flags_03000940.bg2x_l = parameters.x;
    g_control_flags_03000940.bg2x_h = parameters.x >> 16;
    g_control_flags_03000940.bg2y_l = parameters.y;
    g_control_flags_03000940.bg2y_h = parameters.y >> 16;
}
