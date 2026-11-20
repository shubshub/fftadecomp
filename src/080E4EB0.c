#include "ffta.h"

/* Complete target: [0x080E4EB0, 0x080E530E), 1118 bytes, including the
   literal pools. */

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct E4EB0Descriptor {
    u16 phase;
} E4EB0Descriptor;

typedef struct E4EB0State {
    u16 unknown_00;
    u16 timer;
    InterpolationState radius;
    InterpolationState angle;
    InterpolationState center_y;
    InterpolationState scale;
    InterpolationState spin;
    void *upper[6];
    void *lower[6];
    void *effect;
} E4EB0State;

extern const u8 data_084FAB20[];
extern const s16 data_08396E78[];
extern const u8 data_08396FA4[];

extern void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);
extern void *func_080D5CC0(const void *header, u16 index, s16 x, s16 y,
                           s16 height, u8 mode, u8 palette, u8 relative);
extern void func_080110F8(void *object, u8 value);
extern void func_080112E8(void *object, u8 value);
extern void *func_080DFD8C(const void *events, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void func_080D5F74(void **objects, u16 count);
extern s16 func_08007A60(u8 angle);
extern s32 func_08007A4C(u8 angle);
extern s32 func_08141870(s32 numerator, s32 denominator);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);
extern void func_080112CC(void *object, s16 x, s16 y, s16 z);

u32 func_080E4EB0(void *task, E4EB0Descriptor *descriptor, E4EB0State *state)
{
    s16 x[6];
    s16 y[6];
    s16 x2[6];
    s16 y2[6];
    u8 n;
    u8 i;
    u8 j;
    u8 angle;
    u8 angle2;
    s16 radius;
    s16 height;
    s16 scale;
    s32 dx;
    s32 dy;
    s16 dist;
    s16 offset;
    s32 ratio;

    switch (descriptor->phase) {
    case 0:
        state->timer = 120;
        func_080E0608(&state->radius, 150, 0, 120);
        func_080E0608(&state->angle, 0, 255, 40);
        func_080E0608(&state->center_y, 0, 0x60, 120);
        func_080E0608(&state->scale, 0, 0x77, 120);
        func_080E0608(&state->spin, 0, 0x80, 120);
        for (n = 0; n < 6; n++) {
            state->upper[n] = func_080D5CC0(data_084FAB20, 0, 0x100, 0xB0, 0x3FB, 7, 0, 0);
            state->lower[n] = func_080D5CC0(data_084FAB20, 0, 0x100, 0xB0, 0x3FB, 7, 0, 0);
            func_080110F8(state->upper[n], 1);
            func_080110F8(state->lower[n], 1);
            func_080112E8(state->upper[n], 1);
            func_080112E8(state->lower[n], 1);
        }
        state->effect = func_080DFD8C(data_08396FA4, 1, 4, 0, task);
        break;
    case 1:
        func_080D5F74(state->upper, 6);
        func_080D5F74(state->lower, 6);
        break;
    case 0x100:
        radius = (state->radius.current * func_08007A60(state->spin.current)) >> 8;
        height = (state->radius.current * (s16)func_08007A4C(state->spin.current)) >> 8;
        scale = data_08396E78[state->scale.current];
        angle = state->angle.current;
        for (i = 0; i < 3; i++, angle += 0x2A) {
            j = i + 3;
            angle2 = 0xEA - angle;

            dx = func_08007A60(angle);
            dx *= radius;
            dx >>= 8;
            dy = (s16)func_08007A4C(angle);
            dy *= radius;
            dy >>= 9;
            x[i] = dx + 120;
            y[i] = state->center_y.current + dy;
            x[j] = -dx + 120;
            y[j] = state->center_y.current - dy;
            dist = dx;
            if (dist < 0)
                dist = -dist;
            /* 0x080E50FA and 0x080E5190 move the quotient out of r0 before
               the multiplies at 0x080E5108 and 0x080E5196. */
            ratio = func_08141870(dist << 16, radius);
            offset = (height * ratio) >> 16;
            if (dx < 0)
                offset = -offset;
            y[i] += offset;
            y[j] -= offset;

            dx = func_08007A60(angle2);
            dx *= radius;
            dx >>= 8;
            dy = (s16)func_08007A4C(angle2);
            dy *= radius;
            dy >>= 9;
            x2[i] = dx + 120;
            y2[i] = state->center_y.current + dy;
            x2[j] = -dx + 120;
            y2[j] = state->center_y.current - dy;
            dist = dx;
            if (dist < 0)
                dist = -dist;
            ratio = func_08141870(dist << 16, radius);
            offset = (height * ratio) >> 16;
            if (dx > 0)
                offset = -offset;
            y2[i] += offset;
            y2[j] -= offset;

            func_080107D4(state->upper[i], x[i], y[i], 0);
            func_080107D4(state->upper[j], x[j], y[j], 0);
            if (state->spin.current & 0x3F) {
                func_080107D4(state->lower[i], x2[i], y2[i], 0);
                func_080107D4(state->lower[j], x2[j], y2[j], 0);
            } else {
                func_080107D4(state->lower[i], x2[i], 0xB0, 0);
                func_080107D4(state->lower[j], x2[j], 0xB0, 0);
            }
            func_080112CC(state->upper[i], scale, scale, 0);
            func_080112CC(state->upper[j], scale, scale, 0);
            func_080112CC(state->lower[i], scale, scale, 0);
            func_080112CC(state->lower[j], scale, scale, 0);
        }
        func_080E064C(&state->radius);
        func_080E064C(&state->angle);
        func_080E064C(&state->center_y);
        func_080E064C(&state->scale);
        func_080E064C(&state->spin);
        if (func_080E0690(&state->angle))
            func_080E0608(&state->angle, 0, 255, 40);
        if (--state->timer == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
