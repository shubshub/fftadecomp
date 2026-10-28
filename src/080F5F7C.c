#include "ffta.h"

/* 0x080F5F7C..0x080F605E: complete 226-byte callback. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 flags;
} TaskDescriptor;

typedef struct {
    u8 flags;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *underlying;
    u8 unknown_10[8];
    void *coordinate_child;
    void *object_child;
    void *record_child;
} CallbackState;

extern const u8 data_0839B724[];
extern const u8 data_0839B76C[];
extern const u8 data_0839B7B0[];
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080F5F7C(void *task, TaskDescriptor *descriptor, CallbackState *state)
{
    switch (descriptor->phase) {
    case 0:
        state->flags = descriptor->flags;
        state->object = descriptor->object;
        state->underlying = func_080DD748(state->object, &state->x,
                                          &state->y, 0);
        break;
    case 1:
        break;
    case 0x100: {
        u16 mode;
        state->coordinate_child = func_080D6098(state->x, state->y,
            0, 1, 2, state->unknown_10, data_0839B724, task);
        mode = (state->flags & 1) ? 4 : 2;
        state->object_child = func_080DCFE4(state->object, data_0839B76C,
                                           12, 20, mode, task, 20);
        mode = (state->flags & 1) ? 16 : 8;
        state->record_child = func_080DFD8C(data_0839B7B0, 1,
                                           mode | 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child)
            break;
        state->object_child = func_080DBA5C(state->object_child);
        if (!state->object_child)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
