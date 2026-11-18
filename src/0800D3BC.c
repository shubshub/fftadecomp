#include "ffta.h"

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

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    u16 x_low;
    u16 x_high;
    u16 y_low;
    u16 y_high;
} __attribute__((packed)) AffineLine;

typedef struct {
    u16 mode;
    s16 screen_x;
    s16 screen_y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_0A[2];
    struct BgAffineSrc src;
    u8 unknown_20[8];
    u16 line_screen_x;
    u8 unknown_2A[4];
    u16 line_scale_y;
    u16 line_angle;
    u8 unknown_32[2];
    u16 range_mode1;
    u16 range_mode23;
    s16 line_offset_y[160];
    s16 line_scale_x[160];
} AffineWave;

void func_08141864(const struct BgAffineSrc *src, struct BgAffineDst *dst, s32 count);

/* Each row holds BGxPA through BGxY in the order consumed by HBlank DMA. */
void func_0800D3BC(void *state, u16 *destination)
{
    AffineWave *wave = state;
    volatile AffineLine *out = (void *)destination;
    struct BgAffineSrc src;
    struct BgAffineDst row;
    struct BgAffineDst base;
    s16 range = 0;
    s16 start;
    s16 end;
    s32 i;
    s32 dy;
    s32 x;
    s32 y;

    switch (wave->mode) {
    case 1:
        range = wave->range_mode1;
        break;
    case 2:
        range = wave->range_mode23;
        break;
    case 3:
        range = wave->range_mode23;
        break;
    }
    x = (wave->offset_x + wave->screen_x) * 256;
    y = (wave->offset_y + wave->screen_y) * 256;
    wave->src.texX = x;
    wave->src.texY = y;
    wave->src.scrY = wave->screen_y;
    func_08141864(&wave->src, &base, 1);
    src.texX = x;
    src.texY = y;
    src.scrX = wave->line_screen_x;
    src.scrY = wave->screen_y;
    src.sy = wave->line_scale_y;
    src.alpha = wave->line_angle;
    start = 0;
    end = 159;
    if (wave->mode != 0) {
        start = wave->screen_y - range;
        if (start < 0)
            start = 0;
        end = range + wave->screen_y;
    }
    for (i = 0; i < 160; i++) {
        if (i < start || i > end) {
            out->pa = base.pa;
            out->pb = base.pb;
            out->pc = base.pc;
            out->pd = base.pd;
            out->x_low = base.dx;
            out->x_high = base.dx >> 16;
            dy = (wave->offset_y + i) * 256;
            dy += base.dy;
            out->y_low = dy;
            out->y_high = dy >> 16;
        } else {
            src.sx = wave->line_scale_x[i];
            func_08141864(&src, &row, 1);
            dy = wave->line_offset_y[i] + wave->offset_y + i;
            dy *= 256;
            row.dy += dy;
            out->pa = row.pa;
            out->pb = row.pb;
            out->pc = row.pc;
            out->pd = row.pd;
            out->x_low = row.dx;
            out->x_high = row.dx >> 16;
            out->y_low = row.dy;
            out->y_high = row.dy >> 16;
        }
        out++;
    }
}
