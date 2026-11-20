#include "ffta.h"
#include "control_flags.h"

/* Complete target: [0x081168B4, 0x08116AEE), 570 bytes, including the
   literal pools. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    u8 unknown_08[14];
    u16 flags;
} Command081168B4;

typedef struct {
    u16 delay;
    u8 index;
    u8 count;
    u8 flags;
    u8 unknown_05[7];
    void *schedule_task;
    u8 unknown_10[4];
    void *member;
    void *animation;
    void *overlay;
    void *setup_task;
    void *value;
    void *effects[4];
    void *controller;
} State081168B4;

typedef struct {
    u8 unknown_00[0x1C];
} SchedulerDescriptor081168B4;

typedef u32 (*Callback081168B4)(void *task, void *command, void *state);

extern const u8 data_083A3E34[];
extern const u8 data_088F63D8[];
extern const u8 data_0894DCE4[];
extern const u8 data_0894C474[];
extern const u8 data_083A4C78[];
extern const u8 data_083A4C64[];

extern u32 func_08116514(void *task, void *command, void *state);
extern void *func_08005B6C(Callback081168B4 callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DE268(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u16 func_080035A8(u8 index);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080E051C(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern u8 func_080DB838(const void *);
extern u8 func_080D8B4C(void);
extern u8 func_080DBAB8(void **objects, u32 count);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);

u32 func_081168B4(void *task, Command081168B4 *command, State081168B4 *state)
{
    SchedulerDescriptor081168B4 descriptor;

    switch (command->phase) {
    case 0: {
        u8 mode;
        u8 i;

        state->flags = command->flags;
        state->value = command->value;
        mode = 4;
        if (state->flags != 0)
            mode = 0;
        state->setup_task = func_080E03F8(state->value, data_083A3E34, mode, 7,
                                          0, task);
        state->count = func_080DD494(state->value);
        for (i = 0; i < state->count; i++)
            func_080DE268(func_080DD4B4(state->value, i));
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_task = func_080E05DC(state->setup_task);
        if (state->setup_task != 0)
            break;
        func_080D7220(data_088F63D8, 0, 2, 0, 0, 0);
        state->animation = func_080D3E9C(data_0894DCE4, task);
        state->overlay = func_080D4704(data_0894C474, task);
        state->controller = func_080DFD8C(data_083A4C78, 2, 4, 0, task);
        state->delay = 60;
        command->phase++;
        break;
    case 0x101:
        if (--state->delay != 0)
            break;
        state->schedule_task = func_08005B6C(func_08116514, 0x16C,
                                             &descriptor, task);
        command->phase++;
        break;
    case 0x102:
        state->animation = func_080D3F08(state->animation);
        if (state->animation != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay != 0)
            break;
        state->schedule_task = func_080E051C(state->schedule_task);
        if (state->schedule_task != 0)
            break;
        state->delay = 1;
        command->phase++;
        break;
    case 0x103:
        if (--state->delay != 0)
            break;
        state->member = func_080DD4A4(state->value, state->index);
        func_080DB838(func_080DD4C4(state->member));
        command->phase++;
        /* Falls through: the store at 0x08116A56 runs into the 0x104 block
           at 0x08116A58. */
    case 0x104: {
        u32 mode;

        if (func_080D8B4C())
            break;
        func_080DBAB8(state->effects, 4);
        mode = (state->index & 1) ? 4 : 2;
        state->effects[state->index & 3] = func_080DCFE4(state->member,
            data_083A4C64, 12 - (state->index & 6), 10, mode | 8, task, 10);
        if (++state->index == state->count) {
            command->phase++;
            break;
        }
        state->delay = 40;
        command->phase = 0x103;
        break;
    }
    case 0x105:
        if (func_080DBAB8(state->effects, 4))
            command->phase = 2;
        break;
    }
    return 0;
}
