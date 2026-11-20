/* Complete target [0x080EFD50, 0x080F01DE), 1166 bytes including pools. */
#include "ffta.h"
#include "control_flags.h"

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u16 index;
    u16 flags;
    u32 unknown_18;
} Command080EFD50;

typedef struct {
    u16 counter;
    u8 count;
    u8 timer;
    u8 flag;
    u8 unknown_05[3];
    void *children[4];
    InterpolationState x;
    InterpolationState y;
    void *window;
    void *sprite;
    u8 unknown_38[4];
    void *effect;
    void *overlay;
    void *glows[2];
    void *backdrop;
    void *light;
    InterpolationState radius;
    void *object;
    void *initial_child;
    void *script;
} State080EFD50;

typedef u32 (*Callback080EFD50)(void *, Command080EFD50 *, void *);

extern const u8 data_08399BA4[];
extern const u8 data_084FA398[];
extern const u8 data_08399C04[];
extern const u8 data_088F5404[];
extern const u8 data_0894D784[];
extern const u8 data_08399C30[];
extern const u8 data_0894B128[];
extern const u8 data_088F5480[];
extern const u8 data_08949464[];
extern const u8 data_08949438[];
extern const u8 data_088ED5D0[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011058(void *, s16);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern u16 func_080035D0(u8);
extern u16 func_080035A8(u8);
extern u16 func_080035F8(u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080107D4(void *, s16, s16, u8);
extern void func_080D7468(const void *, u8, s16, s16);
extern void *func_080DAB84(u8, s16, s16, void *);
extern void func_080DABB4(void *);
extern u8 func_080DFDF4(void *);
extern void func_080DAC40(void *, s16, s16, u16);
extern void func_080D9B98(void *);
extern void *func_08011484(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D4774(void *);
extern void *func_080D9B64(void *);
extern u8 func_080E0570(void **, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080EFCC0(void *, Command080EFD50 *, void *);
extern void *func_08005B6C(Callback080EFD50, u16, Command080EFD50 *, void *);

u32 func_080EFD50(void *task, Command080EFD50 *command, State080EFD50 *state)
{
    u8 mode;
    u8 index;
    Command080EFD50 descriptor;

    switch (command->phase) {
    case 0:
        state->flag = command->flags;
        state->object = command->object;
        state->timer = 1;
        mode = 8;
        if (state->flag != 0)
            mode = 0;
        state->initial_child = func_080E03F8(state->object, data_08399BA4,
                                             mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->initial_child = func_080E05DC(state->initial_child);
        if (state->initial_child != 0)
            break;
        if (state->flag != 0) {
            state->count = func_080D8858(state->object, 0);
            command->phase = 0x105;
            break;
        }
        state->sprite = func_080D5CC0(data_084FA398, 0, 0xE8, -16, 0x3BF, 6, 1, 0);
        func_08011058(state->sprite, 1);
        state->effect = func_080D6098(0x78, 0x60, 0, 1, 1, state->unknown_38,
                                      data_08399C04, task);
        func_080D7220(data_088F5404, 1, 3, 0xE8, -12, 0);
        state->overlay = func_080D3E9C(data_0894D784, task);
        func_080E0608(&state->x, 0xE8, 0x78, 0x5A);
        func_080E0608(&state->y, -12, 0x60, 0x5A);
        state->counter = 0x5A;
        g_control_flags_03000940.winin_lo = 0x3F & ~func_080035D0(3);
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0xF0;
        g_control_flags_03000940.win0v_hi = 0x90;
        g_control_flags_03000940.win0v_lo = 0xA0;
        g_control_flags_03000940.display |= 0x2000;
        state->script = func_080DFD8C(data_08399C30, 2, 7, 0, task);
        state->backdrop = func_080D4704(data_0894B128, task);
        command->phase++;
        break;
    case 0x101:
        func_080E064C(&state->x);
        func_080E064C(&state->y);
        func_080107D4(state->sprite, state->x.current, state->y.current, 0);
        func_080D7468(data_088F5404, 3, state->x.current, state->y.current);
        if (--state->counter != 0)
            break;
        func_080D7220(data_088F5480, 0, 2, 0, 0, 0);
        state->light = func_080DAB84(0, 0, 0, task);
        func_080DABB4(state->light);
        func_080E0608(&state->radius, 0, 0x9A, 0x3C);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xFF;
        state->glows[0] = func_080D4704(data_08949464, task);
        state->glows[1] = func_080D4704(data_08949438, task);
        func_080DFDF4(state->script);
        command->phase++;
        break;
    case 0x102:
        func_080E064C(&state->radius);
        func_080DAC40(state->light, 0x78, 0x60, state->radius.current);
        func_080D9B98(state->light);
        if (!func_080E0690(&state->radius))
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        command->phase++;
        break;
    case 0x103:
        state->sprite = func_08011484(state->sprite);
        if (state->sprite != 0)
            break;
        func_080D49FC(1, 3, 0, 0x78, 0x60);
        state->window = func_080D4B64(1, data_088ED5D0, 0x288, 8);
        g_control_flags_03000940.bldcnt_lo &= ~func_080035F8(3);
        g_control_flags_03000940.bldcnt_hi |= func_080035F8(3);
        g_control_flags_03000940.display &= 0xDFFF;
        g_control_flags_03000940.display |= func_080035A8(3);
        command->phase++;
        break;
    case 0x104:
        state->window = func_080D4D2C(state->window, 1);
        if (state->window != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        state->effect = func_080D6134(state->effect);
        if (state->effect != 0)
            break;
        state->overlay = func_080D3F08(state->overlay);
        if (state->overlay != 0)
            break;
        if (!func_080D48DC(state->glows, 2))
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->backdrop = func_080D4774(state->backdrop);
        if (state->backdrop != 0)
            break;
        state->light = func_080D9B64(state->light);
        if (state->light != 0)
            break;
        state->count = func_080D8858(state->object, 0);
        if (state->count == 0) {
            command->phase = 2;
            break;
        }
        state->counter = 0;
        command->phase++;
        break;
    case 0x105:
        func_080E0570(state->children, 4);
        if (--state->timer != 0)
            break;
        /* With four children busy the search ends at index 4 (cmp #3; bhi at
         * 0x080F0168) and the store at 0x080F0196 lands on state->x.  No target
         * keeps its slot that long: a child is freed at most 114 frames after
         * its spawn (a KO'd job-99 unit), and spawns are 30 frames apart. */
        for (index = 0; index < 4 && state->children[index] != 0; index++)
            ;
        descriptor.index = state->counter;
        descriptor.object = func_080DD4A4(state->object, state->counter);
        state->children[index] = func_08005B6C(func_080EFCC0, 0x14, &descriptor, task);
        state->timer = 0x1E;
        if (++state->counter == state->count)
            command->phase++;
        break;
    case 0x106:
        if (func_080E0570(state->children, 4))
            command->phase = 2;
        break;
    }
    return 0;
}
