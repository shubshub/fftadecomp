#include "ffta.h"
#include "control_flags.h"

/* Complete [0x0811FFD8, 0x08120398): 960 bytes, including its literal pools. */

typedef struct {
    u16 state;
    u16 unknown_02;
    u8 *output;
    s32 unknown_08;
    u8 unknown_0c[8];
    u16 category;
    u16 variant;
    u16 delay;
    u16 unknown_1a;
} ObjectScript;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 flags;
    u16 timer;
    u8 unknown_04[4];
    u8 index;
    u8 done;
    u8 fading;
    u8 unknown_0b;
    InterpolationState scroll_x;
    InterpolationState scroll_y;
    InterpolationState blend_a;
    InterpolationState blend_b;
    void *child;
} Payload0811FFD8;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern const Point data_083A7928[5];
extern const Point data_083A793C[5];
extern const u8 data_083A7950[5];
extern const u8 data_083A7955[5];
extern const u8 data_083A795A[5];
extern const s16 data_083A7960[5];
extern u8 data_06006000[];

typedef u32 (*ObjectCallback)(void *, ObjectScript *, void *);
extern void *func_08005B6C(ObjectCallback callback, u16 size,
                           ObjectScript *script, void *parent);
extern u32 func_0811FD74(void *, ObjectScript *, void *);
extern void func_080D74E0(u8, u8, u8, s16, s16, void *, void *);
extern u16 func_080035A8(u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080E051C(void *);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern void func_080D4020(void);

u32 func_0811FFD8(void *parent, ObjectScript *script, Payload0811FFD8 *payload)
{
    ObjectScript first;
    ObjectScript second;

    if (payload->flags & 0x8000)
        return 0;

    switch (script->state) {
    case 0:
        payload->index = script->category;
        break;
    case 1:
        break;
    case 0x100:
        func_080D74E0(0, data_083A7950[payload->index], 0,
                      -data_083A7928[payload->index].x,
                      -data_083A7928[payload->index].y,
                      (void *)0x06000000, data_06006000);
        g_control_flags_03000940.display |= func_080035A8(0);
        func_080E0608(&payload->scroll_x, data_083A7928[payload->index].x,
                      data_083A793C[payload->index].x, 0x104);
        func_080E0608(&payload->scroll_y, data_083A7928[payload->index].y,
                      data_083A793C[payload->index].y, 0x104);
        first.category = 0;
        first.variant = data_083A7955[payload->index];
        first.delay = 0x50;
        first.output = &payload->done;
        first.unknown_08 = data_083A7960[payload->index];
        payload->child = func_08005B6C(func_0811FD74, 0x168, &first, parent);
        g_control_flags_03000940.bldcnt_lo = 0x41;
        g_control_flags_03000940.bldcnt_hi = 0x3E;
        func_080E0608(&payload->blend_a, 0, 0, 60);
        func_080E0608(&payload->blend_b, 16, 6, 60);
        script->state++;
        break;
    case 0x101:
        func_080E064C(&payload->scroll_x);
        func_080E064C(&payload->scroll_y);
        func_080E064C(&payload->blend_a);
        func_080E064C(&payload->blend_b);
        func_08003508(-payload->scroll_x.current, 0);
        func_08003558(-payload->scroll_y.current, 0);
        g_control_flags_03000940.bldalpha_lo = payload->blend_a.current;
        g_control_flags_03000940.bldalpha_hi = payload->blend_b.current;
        if (++payload->timer >= 20)
            script->state++;
        break;
    case 0x102:
        if (!func_080E0690(&payload->blend_a)) {
            func_080E064C(&payload->blend_a);
            func_080E064C(&payload->blend_b);
            g_control_flags_03000940.bldalpha_lo = payload->blend_a.current;
            g_control_flags_03000940.bldalpha_hi = payload->blend_b.current;
            if (func_080E0690(&payload->blend_a) && !payload->fading) {
                func_080E0608(&payload->blend_a, 0, 0, 20);
                func_080E0608(&payload->blend_b, 6, 12, 20);
                payload->fading = 1;
            }
        }
        if (payload->child != 0)
            payload->child = func_080E051C(payload->child);
        func_080E064C(&payload->scroll_x);
        func_080E064C(&payload->scroll_y);
        func_08003508(-payload->scroll_x.current, 0);
        func_08003558(-payload->scroll_y.current, 0);
        payload->timer++;
        if (payload->timer == 0x104 - data_083A795A[payload->index]) {
            second.category = 1;
            second.variant = data_083A7955[payload->index];
            second.delay = 0x50;
            second.output = &payload->done;
            second.unknown_08 = data_083A7960[payload->index];
            payload->child = func_08005B6C(func_0811FD74, 0x168, &second, parent);
        }
        if (payload->timer >= 240) {
            func_080E0608(&payload->blend_a, 0, 0, 20);
            func_080E0608(&payload->blend_b, 12, 16, 20);
            script->state++;
        }
        break;
    case 0x103:
        func_080E064C(&payload->scroll_x);
        func_080E064C(&payload->scroll_y);
        func_080E064C(&payload->blend_a);
        func_080E064C(&payload->blend_b);
        func_08003508(-payload->scroll_x.current, 0);
        func_08003558(-payload->scroll_y.current, 0);
        g_control_flags_03000940.bldalpha_lo = payload->blend_a.current;
        g_control_flags_03000940.bldalpha_hi = payload->blend_b.current;
        if (func_080E0690(&payload->scroll_x)) {
            payload->done = 1;
            payload->child = func_080E051C(payload->child);
            if (payload->child == 0)
                script->state++;
        }
        break;
    case 0x104:
        g_control_flags_03000940.display &= ~func_080035A8(0);
        func_080D4020();
        script->state = 2;
        break;
    }
    return 0;
}
