#include "ffta.h"

// Target 0x080FA384, complete [0x080FA384, 0x080FA614), 656 bytes.

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
} Command080FA384;

typedef struct {
    u16 unknown_00;
    u16 unknown_02;
    void *object;
    u8 *ready;
    u8 unknown_0C[8];
    u16 flag;
    u16 unknown_16;
    u32 unknown_18;
} Descriptor080FA384;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 variant;
    u8 ready;
    u8 unknown_07;
    void *task;
    void *target;
    void *input;
    void *pending;
    void *sprite;
    void *effect;
    void *effect2;
    u8 particle_data[12];
    void *particle;
    void *object_effect;
    void *sound;
} State080FA384;

extern const u8 data_0839C63C[];
extern const u8 data_0839C6C8[];
extern const u8 data_0839C710[];
extern const u8 data_088ECD18[];
extern const u8 data_0894D5E8[];
extern const u8 data_08949F18[];
extern const u8 data_0839C76C[];
extern const u8 data_0839C758[];
extern const u8 data_0839C7B4[];
extern const u8 data_0839C7D8[];
extern const u8 data_0839C7E0[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern int func_080F9B14(void *, Descriptor080FA384 *, void *);
extern void *func_08005B6C(int (*)(void *, Descriptor080FA384 *, void *),
                           u16, Descriptor080FA384 *, void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD73C(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4724(const void *, void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080E051C(void *);
extern void *func_080D6134(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_080FA384(void *task, Command080FA384 *command, State080FA384 *state)
{
    Descriptor080FA384 next;
    void *actor;
    u8 mode;

    switch (command->state) {
    case 0:
        state->flag = 0;
        if (command->kind == 0x13D)
            state->flag = 1;
        state->variant = command->option;
        state->input = command->object;
        if (!state->flag)
            mode = 5;
        else
            mode = 6;
        if (state->variant)
            mode = 0;
        if (!state->flag)
            state->pending = func_080E03F8(state->input, data_0839C63C,
                mode, 0, 0, task);
        else
            state->pending = func_080E03F8(state->input, data_0839C6C8,
                mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->pending = func_080E05DC(state->pending);
        if (state->pending)
            break;
        if (func_080D3B54(state->input)) {
            command->state = 2;
            break;
        }
        next.object = state->input;
        next.ready = &state->ready;
        next.flag = state->flag;
        state->task = func_08005B6C(func_080F9B14, 0x1DC, &next, task);
        command->state++;
        break;
    case 0x101:
        if (!state->ready)
            break;
        if (!func_080D8858(state->input, 0)) {
            command->state = 2;
            break;
        }
        actor = func_080DD4A4(state->input, 0);
        state->target = func_080DD748(actor, &state->x, &state->y, 0);
        if (func_080DD73C(state->target))
            state->y -= 8;
        if (!state->flag) {
            state->particle = func_080D6098(state->x, state->y, 0, 1, 3,
                state->particle_data, data_0839C710, task);
        } else {
            func_080D49FC(0, 2, 0, state->x, state->y);
            state->sprite = func_080D4B64(0, data_088ECD18, 0x39F, 6);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940;
                flags |= mask;
                g_control_flags_03000940 = flags;
            }
            state->effect = func_080D3E9C(data_0894D5E8, task);
            state->effect2 = func_080D4724(data_08949F18, task, 4);
            state->particle = func_080D6098(state->x, state->y, 0, 1, 3,
                state->particle_data, data_0839C76C, task);
        }
        if (!state->flag)
            state->object_effect = func_080DCFE4(actor, data_0839C758,
                12, 20, 4, task, 20);
        else
            state->object_effect = func_080DCFE4(actor, data_0839C7B4,
                12, 18, 4, task, 18);
        if (!state->flag)
            state->sound = func_080DFD8C(data_0839C7D8, 1, 4, 0, task);
        else
            state->sound = func_080DFD8C(data_0839C7E0, 2, 4, 0, task);
        command->state++;
        break;
    case 0x102:
        state->task = func_080E051C(state->task);
        if (state->task)
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->sprite = func_080D4D2C(state->sprite, 0);
        if (state->sprite)
            break;
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
        state->effect = func_080D3F08(state->effect);
        if (state->effect)
            break;
        state->effect2 = func_080D4774(state->effect2);
        if (state->effect2)
            break;
        state->object_effect = func_080DBA5C(state->object_effect);
        if (state->object_effect)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
