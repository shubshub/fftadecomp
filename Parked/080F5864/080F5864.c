/* Target: complete [0x080F5864, 0x080F5BE2), 894 bytes, including the
 * fourteen literal words and the alignment padding between the cases. */
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080F5864;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    void *anchor;
    u32 unknown_0C[2];
    u16 mode;
    u16 delay;
    u32 unknown_18;
} Descriptor080F5710;

typedef struct {
    s16 x;
    s16 y;
    u8 flag;
    u8 ready;
    u8 unknown_06;
    u8 count;
    u8 index;
    u8 delay;
    u16 countdown;
    u8 unknown_0C[8];
    void *coordinate_child;
    void *resource_child;
    void *tasks[4];
    void *output;
    void *object;
    void *setup_child;
    void *output_child;
    void *children[4];
    void *record_child;
} State080F5864;

extern const u8 data_0839B418[];
extern const u8 data_0839B454[];
extern const u8 data_0839B46C[];
extern const u8 data_0839B49C[];
extern const u8 data_0839B4B0[];
extern const u8 data_0839B4B4[];
extern const u8 data_0839B4B8[];
extern const u8 data_0839B4C0[];
extern const u8 data_0894AD30[];

extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16,
                           u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                           void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u8, u8 *, const void *, u16, u16, void *);
extern void *func_080D4724(const void *, void *, u16);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080F5710(void *, Descriptor080F5710 *, void *);
extern void *func_08005B6C(void *callback, int size,
                           Descriptor080F5710 *descriptor, void *owner);
extern u8 func_080E0570(void **, int);
extern void *func_080D4774(void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_080F5864(void *task, Descriptor080F5864 *descriptor,
                  State080F5864 *state)
{
    Descriptor080F5710 child;
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        state->flag = descriptor->flag;
        state->object = descriptor->object;
        mode = 5;
        if (state->flag)
            mode = 0;
        state->setup_child = func_080E03F8(state->object, data_0839B418,
                                           mode, 0, 0, task);
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
            descriptor->phase = 0x105;
        } else {
            state->output_child = func_080DDF68(state->object, &state->output,
                0x90, 1, &state->ready, data_0839B4B0, 0, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (!state->ready)
            break;
        func_080DBDC8(state->output, &state->x, &state->y);
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
            1, state->unknown_0C, data_0839B454, task);
        state->record_child = func_080DFD8C(data_0839B4B8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        func_080DE3BC(state->output, 0);
        func_080DBA50(state->output_child);
        state->output_child = func_080DE4F4(state->output, 1, &state->ready,
                                            data_0839B4B4, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (!state->ready)
            break;
        state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
            2, state->unknown_0C, data_0839B46C, task);
        state->record_child = func_080DFD8C(data_0839B4C0, 1, 4, 0, task);
        func_080DBA50(state->output_child);
        state->resource_child = func_080D4724(data_0894AD30, task, 10);
        state->countdown = 20;
        descriptor->phase++;
        break;
    case 0x104: {
        u16 delay;
        u8 i;
        if (--state->countdown)
            break;
        state->count = func_080D8858(state->object, 0);
        if (!state->count) {
            descriptor->phase = 2;
            break;
        }
        delay = 0;
        for (i = 0; i < state->count; i++) {
            child.mode = i;
            child.delay = delay;
            child.object = func_080DD4A4(state->object, i);
            child.anchor = state->object;
            state->tasks[i] = func_08005B6C(func_080F5710, 0x1C, &child, task);
            delay++;
        }
        descriptor->phase++;
        break;
    }
    case 0x105:
        if (!func_080E0570(state->tasks, 4))
            break;
        state->resource_child = func_080D4774(state->resource_child);
        if (state->resource_child)
            break;
        state->delay = 1;
        descriptor->phase++;
        break;
    case 0x106:
        func_080DBFFC(state->object, state->index);
        descriptor->phase++;
    case 0x107: {
        void *object;
        u32 parity;
        u16 flags;
        if (func_080D8B4C())
            break;
        if (--state->delay)
            break;
        object = func_080DD4A4(state->object, state->index);
        parity = state->index & 1;
        flags = parity ? 4 : 2;
        state->children[state->index] = func_080DCFE4(object, data_0839B49C,
            12 - parity, 0, flags | 8, task, 0);
        state->delay = 40;
        state->index++;
        if (state->index != state->count)
            descriptor->phase = 0x106;
        else
            descriptor->phase++;
        break;
    }
    case 0x108: {
        u8 complete;
        u8 i;
        if (!func_080DE1F0(state->output))
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
