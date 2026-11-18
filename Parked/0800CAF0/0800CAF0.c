#include "ffta.h"

typedef struct {
    u16 left;
    u16 right;
} CircleSpan;

typedef struct {
    s32 x, y, endX, endY, stepX, stepY;
    s32 deltaX, deltaY, accumulator, error, remaining;
} LineState;

typedef struct {
    u16 mode;
    s16 screen_x;
    s16 screen_y;
    u8 unknown_06[0x2E];
    u16 radius_x;
    u16 radius_y;
    s16 line_offset_y[160];
    s16 line_scale_x[160];
} AffineWave;

extern void func_0800EA0C(s16 center_x, s16 center_y, u16 radius_x, u16 radius_y,
                          CircleSpan *spans, u8 clip);
extern void func_080075CC(LineState *line, s32 x, s32 y, s32 end_x, s32 end_y);
extern void func_080076A0(LineState *line);
extern s16 func_08007A60(u8 angle);

void func_0800CAF0(AffineWave *wave, u8 make_offsets)
{
    union {
        CircleSpan spans[160];
        u32 words[160];
    } rows;
    LineState line;
    int radius_x = wave->radius_x;
    int radius_y = wave->radius_y;
    int i;
    int numerator;

    for (i = 0; i < 160; i++) {
        rows.spans[i].left = 245;
        rows.spans[i].right = 250;
    }
    func_0800EA0C(wave->screen_x, wave->screen_y, radius_x, radius_y, rows.spans, 1);

    numerator = (s32)((u32)(2 * radius_x + 1) << 16);
    for (i = 0; i < 160; i++) {
        if (rows.words[i] == 0x00FA00F5)
            wave->line_scale_x[i] = 256;
        else {
            int width = (s16)rows.spans[i].right - (s16)rows.spans[i].left;
            wave->line_scale_x[i] = (numerator / width) >> 8;
        }
    }
    if (make_offsets) {
        s16 *offsets = wave->line_offset_y;
        int start = (u16)wave->screen_y - radius_y;
        u16 height = 2 * radius_y + 1;
        u16 count = start + height;

        func_080075CC(&line, 0, 0, 128, height - 1);
        for (i = 0; i < count; i++) {
            s16 offset = func_08007A60(line.x) * (radius_y >> 1);
            offsets[start + i] = offset >> 8;
            func_080076A0(&line);
        }
    }
}
