#include "ffta.h"

/* Target: 0x080E7F4C, 524 bytes including literal pools. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 variant;
    u32 unknown_18;
} Task080E7F4C;

typedef struct {
    u8 kind;
    u8 variant;
    u8 count;
    u8 index;
    u8 delay;
    u8 special;
    u8 ready;
    u8 unknown_07;
    void *display;
    void *request;
    void *object;
    void *children[2];
    void *transition;
} State080E7F4C;

extern const u8 data_08397C00[];
extern const void *data_08397BF4[];
extern const u8 data_08397CFC[];
extern const u8 data_08397CE0[];
extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u32, u32, u8 *, const void *, u32, u32, void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u32);
extern u8 func_080E0570(void **, u32);
extern void *func_080DD4A4(void *, u32);
extern u32 func_080E7D20(void *, Task080E7F4C *, void *);
extern void *func_08005B6C(u32 (*)(void *, Task080E7F4C *, void *), u32, Task080E7F4C *, void *);
extern u8 func_080DE1F0(void *);

u32 func_080E7F4C(void *owner, Task080E7F4C *task, State080E7F4C *state)
{
    Task080E7F4C child;
    u32 mode;
    u32 speed;
    u8 slot;

    switch (task->phase) {
    case 0:
        if (task->kind != 231) {
            state->kind = task->kind - 24;
            state->special = 0;
            mode = 1;
        } else {
            state->kind = 0;
            state->special = 1;
            mode = 0;
        }
        state->variant = task->variant;
        state->object = task->object;
        speed = data_08397C00[state->kind];
        if (state->variant)
            speed = 0;
        state->transition = func_080E03F8(state->object, data_08397BF4[state->kind], speed, mode, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 256:
        state->transition = func_080E05DC(state->transition);
        if (!state->transition) {
            if (state->special) {
                if (func_080D3B54(state->object)) {
                    task->phase = 2;
                } else {
                    state->request = func_080DDF68(state->object, &state->display, 0x8007, 2,
                        &state->ready, data_08397CFC, 5, 0, owner);
                    task->phase++;
                }
            } else {
                task->phase = 259;
            }
        }
        break;
    case 257:
        if (state->ready) {
            func_080D8CD4(state->object);
            state->index = 4;
            task->phase++;
        }
        break;
    case 258:
        if (state->index && --state->index)
            break;
        if (!func_080D8B4C())
            task->phase++;
        break;
    case 259:
        state->count = func_080D8858(state->object, 0);
        if (state->count) {
            state->delay = 1;
            task->phase++;
        } else {
            task->phase = 2;
        }
        break;
    case 260:
        func_080E0570(state->children, 2);
        state->delay--;
        if (!state->delay) {
            slot = state->children[0] != 0;
            child.kind = state->kind;
            child.variant = state->index;
            child.object = func_080DD4A4(state->object, state->index);
            state->children[slot] = func_08005B6C(func_080E7D20, 0x34, &child, owner);
            state->delay = data_08397CE0[state->kind];
            state->index++;
            if (state->index == state->count)
                task->phase++;
        }
        break;
    case 261:
        if (state->special && !func_080DE1F0(state->display))
            break;
        if (func_080E0570(state->children, 2))
            task->phase = 2;
        break;
    }
    return 0;
}
