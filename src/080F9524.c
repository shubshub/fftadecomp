#include "control_flags.h"

typedef struct {
    u16 phase;
} Descriptor;

typedef struct {
    u16 radius;
    s16 remaining, error, step, period, distance;
} Interpolation;

typedef struct {
    u16 unused_00;
    s16 x, y, horizontal, vertical;
    u8 unknown_0A[2];
    void *sequence, *animation, *timed_animation, *window, *scanlines;
    u8 unknown_20[8];
    Interpolation opening;
} Effect;

typedef struct {
    s32 x, y;
    u8 unknown_08[4];
    u16 parameter;
    u8 unknown_0E[6];
} Scanline;

typedef struct {
    u8 unknown_00[0x320];
    Scanline lines[80];
} ScanlineBuffer;

extern const u8 data_088F58D4[], data_0894D69C[], data_08949D10[], data_08949F18[];
typedef struct __attribute__((packed)) {
    u16 count;
    u16 values[80];
} ScanlineParameters;

extern const ScanlineParameters data_0894E968;
extern const s16 data_0839C554[];

extern void func_080D73AC(const void *, u8, u8, s16, s16, u8);
extern u16 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const u8 *, void *, u16);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern u16 func_080035D0(u8);
extern void *func_080D99C0(u8, u32, u32, s16, s16, u16, u16, u16, void *);
extern ScanlineBuffer *func_080D9A14(void *);
extern void func_08003620(u8);
extern void func_080E0608(Interpolation *, s16, s16, s16);
extern void func_080E064C(Interpolation *);
extern void func_080DAC40(void *, s16, s16, u16);
extern u8 func_080E0690(Interpolation *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D9B64(void *);

static inline Scanline *scanline_at(ScanlineBuffer *buffer, u16 i)
{
    return (Scanline *)(i * sizeof(Scanline) + (u32)buffer + sizeof(buffer->unknown_00));
}

static inline void advance_scanlines(void *scanlines, s16 *horizontal, s16 *vertical)
{
    if (scanlines) {
        ScanlineBuffer *buffer = func_080D9A14(scanlines);
        s32 x = ((*horizontal) >> 2) * 256;
        s32 y = ((*vertical) >> 1) * 256;
        u16 i;
        for (i = 0; i < 80; i++) {
            Scanline *line = scanline_at(buffer, i);
            line->x = x;
            line->y = y + data_0839C554[i];
        }
        (*horizontal)--;
        (*vertical)--;
    }
}

static inline void *create_scanlines(s16 x, s16 y, void *owner)
{
    void *scanlines;
    ScanlineBuffer *buffer;
    const ScanlineParameters *parameters;
    u16 i;
    scanlines = func_080D99C0(2, 0x2800, 0x2800, x, y,
                              0x100, 0x100, 0, owner);
    buffer = func_080D9A14(scanlines);
    parameters = &data_0894E968;
    for (i = 0; i < parameters->count; i++) {
        Scanline *line = scanline_at(buffer, i);
        line->parameter = parameters->values[i];
    }
    func_080D9BA8(scanlines, 1);
    func_08003620(1);
    return scanlines;
}

/* 080F9524..080F9838, 788 bytes including literal pools. */
int func_080F9524(void *owner, Descriptor *descriptor, Effect *effect)
{
    switch (descriptor->phase) {
    case 0:
        effect->x = 120;
        effect->y = 80;
        break;
    case 0x100: {
        void *window;

        func_080D73AC(data_088F58D4, 0, 2, effect->x, effect->y, 1);
        g_control_flags_03000940.display |= func_080035A8(2);
        effect->sequence = func_080D3E9C(data_0894D69C, owner);
        effect->animation = func_080D4704(data_08949D10, owner);
        effect->timed_animation = func_080D4724(data_08949F18, owner, 80);
        window = func_080DAB84(0, 0, 0, owner);
        func_080D9BA8(window, 1);
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 255;
        g_control_flags_03000940.display |= 0x2000;
        effect->window = window;

        effect->scanlines = create_scanlines(effect->x, effect->y, owner);
        func_080E0608(&effect->opening, 0, 40, 24);
        descriptor->phase++;
        break;
    }
    case 0x101:
        advance_scanlines(effect->scanlines, &effect->horizontal, &effect->vertical);
        func_080E064C(&effect->opening);
        func_080DAC40(effect->window, effect->x, effect->y, effect->opening.radius);
        if (func_080E0690(&effect->opening))
            descriptor->phase++;
        break;
    case 0x102:
        advance_scanlines(effect->scanlines, &effect->horizontal, &effect->vertical);
        if ((effect->sequence = func_080D3F08(effect->sequence))) break;
        if ((effect->animation = func_080D4774(effect->animation))) break;
        if ((effect->timed_animation = func_080D4774(effect->timed_animation))) break;
        if ((effect->window = func_080D9B64(effect->window))) break;
        if ((effect->scanlines = func_080D9B64(effect->scanlines))) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        g_control_flags_03000940.display &= ~0x2000;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
