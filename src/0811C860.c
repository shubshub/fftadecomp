#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x0811C860, 0x0811CA6E), 526 bytes, 263 halfwords.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u8 kind;
} Command0811C860;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[20];
} Descriptor0811C860;

typedef struct {
    u8 unknown_00[2];
    u8 kind;
    u8 ready;
    s16 x;
    s16 y;
    void *object;
    void *palette_task;
    void *tasks[3];
    void *initial_task;
    void *overlay;
    void *effect;
    void *child;
    void *sprite;
} State0811C860;

typedef u32 (*Callback0811C860)(void *, Descriptor0811C860 *, void *);

extern const u8 data_083A6C7C[];
extern const u8 data_088F58EC[];
extern const u8 data_0894C7E4[];
extern const u8 data_0894C818[];
extern const u8 data_0894A07C[];
extern const u8 data_0894A0B0[];
extern const u8 data_0894AC90[];
extern const u8 data_0894D69C[];
extern const u8 data_083A6CDC[];
extern u8 data_0600DF60[];
extern u8 data_06005000[];

extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080D7A70(const void *, u8, void *);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *);
extern void func_080DE10C(void *object, u16 value);
extern void *func_080DE4B0(void *object, u8 *finished, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *context);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *resource, void *context);
extern void *func_080D3E9C(const void *resource, void *context);
extern void *func_080DFD8C(const void *resource, u8 count, u16 flags,
                           u16 delay, void *context);
extern void *func_080D3F08(void *handle);
extern u8 func_080D48DC(void **tasks, u16 count);
extern u32 func_080035A8(u8 index);
extern void *func_080DFA70(void *, u32, u32, u32, u32, u32, void *, void *, u32, u32, void *);
extern void *func_08005B6C(Callback0811C860, u16, Descriptor0811C860 *, void *);
extern void *func_080E051C(void *);
extern void *func_080DBA5C(void *);
extern u32 func_0811C50C(void *, Descriptor0811C860 *, void *);
extern u32 func_0811C6B0(void *, Descriptor0811C860 *, void *);

u32 func_0811C860(void *task, Command0811C860 *command, State0811C860 *state)
{
    switch (command->phase) {
    case 0:
        state->kind = command->kind - 0x7d;
        state->object = command->object;
        func_080DBDC8(state->object, &state->x, &state->y);
        state->initial_task = func_080D7A70(data_083A6C7C, 8, task);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        state->initial_task = func_080D7ABC(state->initial_task);
        if (state->initial_task != 0)
            break;
        if (state->kind == 1) {
            func_080DE10C(state->object, 0x58);
            state->overlay = func_080DE4B0(state->object, &state->ready,
                                           2, 2, 0, 0, 0, task);
        } else {
            state->ready = 1;
        }
        command->phase++;
        break;
    case 0x101:
        if (state->ready == 0)
            break;
        func_080D7220(data_088F58EC, 0, 2, state->x, state->y, 0);
        if (state->kind != 2) {
            state->tasks[0] = func_080D4704(data_0894C7E4, task);
            state->tasks[1] = func_080D4704(data_0894C818, task);
        } else {
            state->tasks[0] = func_080D4704(data_0894A07C, task);
            state->tasks[1] = func_080D4704(data_0894A0B0, task);
        }
        state->tasks[2] = func_080D4704(data_0894AC90, task);
        state->palette_task = func_080D3E9C(data_0894D69C, task);
        state->sprite = func_080DFD8C(data_083A6CDC, 1, 4, 0, task);
        command->phase++;
        break;
    case 0x102:
        state->palette_task = func_080D3F08(state->palette_task);
        if (state->palette_task != 0)
            break;
        if (!func_080D48DC(state->tasks, 3))
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        command->phase++;
        break;
    case 0x103: {
        Descriptor0811C860 request;
        if (state->kind != 1) {
            state->effect = func_080DFA70(state->object, 3, 7, 7, 0x3ed, 0x3e6,
                                          data_0600DF60, data_06005000, 0, 0, task);
            if (state->kind == 2) {
                request.object = state->object;
                state->child = func_08005B6C(func_0811C6B0, 0x5c, &request, task);
            }
        } else {
            request.object = state->object;
            state->child = func_08005B6C(func_0811C50C, 0x1c, &request, task);
        }
        command->phase++;
        break;
    }
    case 0x104:
        state->child = func_080E051C(state->child);
        if (state->child != 0)
            break;
        state->effect = func_080DBA5C(state->effect);
        if (state->effect == 0)
            command->phase = 2;
        break;
    }
    return 0;
}
