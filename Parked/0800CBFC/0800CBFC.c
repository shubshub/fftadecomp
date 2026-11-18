#include "ffta.h"

typedef struct {
    u16 mode;
    s16 center_x;
    s16 center_y;
    u8 unknown_06[0x2E];
    u16 radius_x;
    u16 radius_y;
    s16 line_offset_y[160];
    s16 line_scale_x[160];
} AffineWave;

struct Span0800F6A8 {
    u16 left;
    u16 right;
};

extern void func_0800F6A8(s16 x, s16 y, u16 radius_x, u16 radius_y,
                           struct Span0800F6A8 *spans, u8 clip);

/* The span builders mark untouched scanlines with left 245 and right 250. */
typedef union {
    struct Span0800F6A8 bounds[160];
    u32 words[160];
} SpanRows;

static inline void clear_spans(struct Span0800F6A8 *rows)
{
    int i;
    for (i = 0; i < 160; i++) {
        rows[i].left = 245;
        rows[i].right = 250;
    }
}

static inline void set_scales(s16 *scales, SpanRows *spans, u16 radius_y)
{
    int i;
    s32 diameter = (u32)(2 * radius_y + 1) << 16;

    for (i = 0; i < 160; i++) {
        if (spans->words[i] == (245u | (250u << 16))) {
            scales[i] = 256;
        } else {
            s32 width = (s16)spans->bounds[i].right - (s16)spans->bounds[i].left;
            scales[i] = (diameter / width) >> 8;
        }
    }
}

void func_0800CBFC(AffineWave *wave)
{
    SpanRows spans;
    u16 radius_x = wave->radius_x;
    u16 radius_y = wave->radius_y;

    clear_spans(spans.bounds);
    func_0800F6A8(wave->center_x, wave->center_y, radius_x, radius_y, spans.bounds, 1);
    set_scales(wave->line_scale_x, &spans, radius_y);
}
