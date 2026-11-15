#include "ffta.h"

/* Target: complete [0x081086D0, 0x08108A74), 932 bytes, 393 reachable instructions.
 * Phase callback that spawns up to four func_08108630 children.
 * Local offset views; original declaration types and extents are unknown. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u8 type;
    u8 unknown_15;
    u16 flag;
} Descriptor;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 slot;
    u16 delay;
    u16 selector;
} ChildDescriptor;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 kind;
    u8 type;
    u8 count;
    u8 index;
    u8 delay;
    u8 unknown_0B[5];
    void *resource_child;
    void *timed_child;
    void *effect_object;
    void *script_child;
    void *tasks[4];
    void *actor;
    void *object;
    void *setup_child;
    void *output_child;
    void *children[4];
    void *record_child;
} State;

typedef u32 (*Callback)(void *, void *, void *);

extern const void *const data_083A1038[];
extern const u8 data_083A1050[];
extern const void *const data_083A1058[];
extern const u16 data_083A1070[];
extern const void *const data_083A1094[];
extern const u8 data_083A10AC[];
extern const u8 data_083A10C0[];
extern const u8 data_083A10C4[];
extern const u8 data_0894A26C[];
extern const u8 data_0894D69C[];
extern u16 g_control_flags_03000940;

extern u32 func_08108630(void *, void *, void *);
extern void *func_08005B6C(Callback, u16, void *, void *);
extern void *func_080DD47C(void *);
extern u8 func_080DBC88(void *);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern u16 func_080DD6F4(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16,
                           u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BE10(void *, u8);
extern u32 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D3E9C(const void *, void *);
extern u8 func_080D8924(void *, u8, u16, void *);
extern void *func_080DD4B4(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u8 func_080E0570(void **, u8);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_081086D0(void *task, Descriptor *descriptor, State *state)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        state->type = descriptor->type - 0x7c;
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        state->actor = func_080DD47C(state->object);
        state->kind = func_080DBC88(state->actor);
        state->type <<= 1;
        if (state->kind == 1 || state->kind == 2)
            state->type++;
        mode = data_083A1050[state->type];
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object,
                                           data_083A1038[state->type], mode,
                                           1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child)
            break;
        if (state->flag) {
            state->count = func_080DD494(state->object);
            state->delay = 1;
            descriptor->phase = 0x103;
        } else {
            u16 height = 0x98;

            if (func_080DD6F4(state->actor) == 9)
                height = 0x54;
            state->output_child = func_080DDF68(state->object, 0, height, 1,
                                                &state->ready, data_083A10C0,
                                                0, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101: {
        ChildDescriptor child;
        u8 delays[5] = {0, 40, 30, 20, 10};
        u16 delay;
        u8 i;

        if (!state->ready)
            break;
        func_080DBDC8(state->actor, &state->x, &state->y);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->effect_object = func_080D4B64(0, data_083A1058[state->type],
                                             data_083A1070[state->type], 6);
        if (state->kind > 1)
            func_0800BE10(state->effect_object, 1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        state->resource_child = func_080D4704(data_0894A26C, task);
        state->timed_child = func_080D4724(data_083A1094[state->type], task,
                                           0x10);
        state->script_child = func_080D3E9C(data_0894D69C, task);
        state->count = func_080D8924(state->object, 0, 0x1e, task);
        delay = delays[state->count];
        for (i = 0; i < state->count; i++) {
            child.slot = i;
            child.delay = delay;
            child.selector = state->type;
            child.actor = func_080DD4B4(state->object, i);
            state->tasks[i] = func_08005B6C(func_08108630, 0x10, &child, task);
            delay += 10;
        }
        state->record_child = func_080DFD8C(&data_083A10C4[(state->type >> 1) * 8],
                                            1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102:
        state->effect_object = func_080D4D2C(state->effect_object, 0);
        if (state->effect_object)
            break;
        {
            u32 mask = func_080035A8(2);

            g_control_flags_03000940 &= ~mask;
        }
        state->script_child = func_080D3F08(state->script_child);
        if (state->script_child)
            break;
        state->resource_child = func_080D4774(state->resource_child);
        if (state->resource_child)
            break;
        state->timed_child = func_080D4774(state->timed_child);
        if (state->timed_child)
            break;
        if (!func_080E0570(state->tasks, 4))
            break;
        state->count = func_080DD494(state->object);
        if (!state->count) {
            descriptor->phase = 2;
        } else {
            state->delay = 1;
            descriptor->phase++;
        }
        break;
    case 0x103:
        func_080DBFFC(state->object, state->index);
        descriptor->phase++;
    case 0x104: {
        void *object;
        u16 flags;

        if (func_080D8B4C())
            break;
        if (--state->delay)
            break;
        object = func_080DD4A4(state->object, state->index);
        flags = (state->index & 1) ? 4 : 2;
        state->children[state->index] = func_080DCFE4(object, data_083A10AC,
                                                      12, 0, flags | 8, task,
                                                      0);
        state->delay = 30;
        state->index++;
        if (state->index != state->count)
            descriptor->phase = 0x103;
        else
            descriptor->phase++;
        break;
    }
    case 0x105: {
        u8 complete;
        u8 i;

        if (!func_080DE1F0(state->actor))
            break;
        complete = 1;
        for (i = 0; i < 4; i++) {
            state->children[i] = func_080DBA5C(state->children[i]);
            if (state->children[i])
                complete = 0;
        }
        if (complete)
            descriptor->phase = 2;
        break;
    }
    }
    return 0;
}
