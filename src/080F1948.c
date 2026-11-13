#include "ffta.h"
#include "control_flags.h"

// 0x080F1948..0x080F1AEC: 420 bytes.
typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080F1948;

typedef struct {
    s16 x;
    s16 y;
    u8 frame;
    u8 unknown_05[3];
    u32 background;
    u32 task_a;
    u32 task_b;
    u32 task_c;
    u32 payload;
    u32 effect;
    Interpolation080F1948 fade;
} State080F1948;

typedef struct {
    u16 state;
    u16 unknown_02;
    u32 value;
} Command080F1948;

typedef struct {
    s32 texture_x;
    s32 texture_y;
    s16 screen_x;
    s16 screen_y;
    s16 scale_x;
    s16 scale_y;
    u16 angle;
} AffineSource080F1948;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineTransform080F1948;

extern const u16 data_0839A50C[];
extern const u8 data_0839A584[];
extern const u8 data_088F104C[];
extern const u8 data_0894DB48[];
extern const u8 data_089492DC[];
extern const u8 data_0894B268[];

extern void func_080D49FC(u32 first, u32 second, u32 third, s16 x, s16 y);
extern void func_0800BC90(u32 first, u32 second, u32 third);
extern u32 func_080D4B64(u32 index, const void *resource, u16 size, u32 type);
extern void func_08003620(u8 value);
extern u32 func_080035A8(u8 layer);
extern u32 func_080D3E9C(const void *resource, void *parent);
extern u32 func_080D4704(const void *resource, void *parent);
extern u32 func_080D3F08(u32 task);
extern u32 func_080D4774(u32 task);
extern u32 func_080D4D2C(u32 handle, u8 index);
extern void func_080E0608(Interpolation080F1948 *state, s16 from, s16 to, u16 duration);
extern void func_080E064C(Interpolation080F1948 *state);
extern u8 func_080E0690(Interpolation080F1948 *state);
extern u32 func_080DFD8C(const void *resource, u8 parameter, u32 type, u32 flags, void *context);
extern void func_08141864(const AffineSource080F1948 *src, AffineTransform080F1948 *dst, int count);
extern void func_080032F8(const AffineTransform080F1948 *transform, u8 layer);

u32 func_080F1948(void *context, Command080F1948 *command, State080F1948 *state)
{
    switch (command->state) {
    case 0:
        state->payload = command->value;
        state->x = 120;
        state->y = 40;
        break;
    case 0x100:
        func_080D49FC(0, 2, 1, state->x, state->y);
        func_0800BC90(0, 0, 2);
        state->background = func_080D4B64(0, data_088F104C, 186, 6);
        func_08003620(1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;
            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        state->task_a = func_080D3E9C(data_0894DB48, context);
        state->task_b = func_080D4704(data_089492DC, context);
        state->task_c = func_080D4704(data_0894B268, context);
        func_080E0608(&state->fade, 0, -128, 28);
        state->effect = func_080DFD8C(data_0839A584, 1, 4, 0, context);
        command->state++;
        break;
    case 0x101: {
        AffineSource080F1948 src;
        AffineTransform080F1948 dst;

        func_080E064C(&state->fade);
        src.texture_x = 0x2000;
        src.texture_y = 0x3000;
        src.screen_x = state->x;
        src.screen_y = state->y;
        src.scale_x = data_0839A50C[state->frame];
        src.scale_y = data_0839A50C[state->frame];
        src.angle = state->fade.current << 8;
        func_08141864(&src, &dst, 1);
        func_080032F8(&dst, 2);
        state->frame++;
        if (func_080E0690(&state->fade))
            command->state++;
        break;
    }
    case 0x102:
        state->task_a = func_080D3F08(state->task_a);
        if (state->task_a)
            break;
        state->task_b = func_080D4774(state->task_b);
        if (state->task_b)
            break;
        state->task_c = func_080D4774(state->task_c);
        if (state->task_c)
            break;
        state->background = func_080D4D2C(state->background, 0);
        if (state->background)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        command->state = 2;
        break;
    }
    return 0;
}
