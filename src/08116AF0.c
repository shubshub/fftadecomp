// Target: complete [0x08116AF0, 0x08116CB0), 448 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    u8 unknown_08[14];
    u16 flags;
} Command08116AF0;

typedef struct {
    s16 x;
    s16 y;
    u8 flags;
    u8 selector;
    u16 delay;
    void *schedule_task;
    void *overlay;
    void *effect;
    void *animation;
    void *value;
    void *setup_task;
    void *controller;
} State08116AF0;

typedef struct {
    u8 unknown_00[4];
    void *value;
    u32 unknown_08;
    u32 unknown_0c;
    u8 unknown_10[4];
    u16 phase;
    u16 flags;
    u8 unknown_18[4];
} SchedulerDescriptor08116AF0;

typedef u32 (*Callback08116AF0)(void *task, void *command, void *state);

extern const u8 data_083A4CB0[];
extern const u8 data_083A4CD4[];
extern const u8 data_088F06B0[];
extern const u8 data_0894DAA0[];
extern const u8 data_0894AB50[];
extern u16 g_control_flags_03000940;

extern u32 func_080E7C04(void *task, void *command, void *state);
extern void *func_08005B6C(Callback08116AF0 callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void func_080D8C58(void *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u32 index);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8924(void *, u8, u8, void *);
extern void *func_080D4D2C(void *, u32);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080E051C(void *);

u32 func_08116AF0(void *task, Command08116AF0 *command, State08116AF0 *state)
{
    SchedulerDescriptor08116AF0 descriptor;
    u16 *control_flags;
    u32 mask;
    u32 flags;

    switch (command->phase) {
    case 0: {
        u8 mode;

        state->flags = command->flags;
        state->value = command->value;
        mode = 3;
        if (state->flags != 0)
            mode = 0;
        state->setup_task = func_080E03F8(state->value, data_083A4CB0, mode, 1,
                                          0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_task = func_080E05DC(state->setup_task);
        if (state->setup_task != 0)
            break;
        if (state->flags != 0) {
            state->selector = func_080DD494(state->value);
            command->phase = 0x102;
            break;
        }
        command->phase++;
        break;
    case 0x101:
        func_080D8C58(state->value, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->effect = func_080D4B64(0, data_088F06B0, 0x320, 6);
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        state->animation = func_080D3E9C(data_0894DAA0, task);
        state->overlay = func_080D4704(data_0894AB50, task);
        state->controller = func_080DFD8C(data_083A4CD4, 1, 4, 0, task);
        state->selector = func_080D8924(state->value, 0, 30, task);
        if (state->selector == 0) {
            command->phase = 0x103;
            break;
        }
        state->delay = 38;
        command->phase++;
        break;
    case 0x102:
        state->delay--;
        if (state->delay != 0)
            break;
        descriptor.phase = 0x13C;
        descriptor.flags = state->flags;
        descriptor.value = state->value;
        descriptor.unknown_08 = 0;
        descriptor.unknown_0c = 1;
        state->schedule_task = func_08005B6C(func_080E7C04,
                                             0x14, &descriptor, task);
        command->phase++;
        break;
    case 0x103:
        state->effect = func_080D4D2C(state->effect, 0);
        if (state->effect != 0)
            break;
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags & ~mask;
        state->animation = func_080D3F08(state->animation);
        if (state->animation != 0)
            break;
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay != 0)
            break;
        state->schedule_task = func_080E051C(state->schedule_task);
        if (state->schedule_task != 0)
            break;
        command->phase = 2;
        break;
    }
    return 0;
}
