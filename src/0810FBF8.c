#include "ffta.h"

// Target 0x0810FBF8..0x0810FD78, 384 bytes including literal pools.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *argument;
    u8 unknown_08[0xC];
    s16 unknown_14;
    u16 mode;
} Request;

typedef struct {
    u16 x;
    u16 y;
    u8 mode;
    u8 unknown_05[3];
    void *task0;
    void *task1;
    void *task2;
    void *object;
    void *argument;
    void *task3;
    void *task4;
} State;

typedef struct {
    u32 unknown_00;
    void *argument;
    u8 unknown_08[0xC];
    u16 x;
    u16 y;
    u8 unknown_18[4];
} Descriptor;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern const u8 data_083A2D64[];
extern u32 func_0810EA78(void *task, void *request, void *payload);
extern u32 func_0810EF0C(void *task, void *request, void *payload);
extern u32 func_0810FAF8(void *task, void *request, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                         void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void *func_080E05DC(void *);
extern void *func_080E051C(void *);
extern void *func_080DFD68(int, int, void *);
extern void *func_080DFED8(void *);
extern void *func_08115AE4(void *, int, void *);
extern void *func_08115B40(void *);
extern void func_080D38B4(void);
extern void func_0801E6F0(u16 *first, u16 *second);

u32 func_0810FBF8(void *owner, Request *request, State *state)
{
    Descriptor first;
    Descriptor second;
    Descriptor third;
    u32 kind;

    switch (request->phase) {
    case 0:
        state->mode = request->mode;
        state->argument = request->argument;
        kind = 8;
        if (state->mode)
            kind = 0;
        state->object = func_080E03F8(state->argument, data_083A2D64, kind, 7, 0,
                                      owner);
        func_0801E6F0(&state->x, &state->y);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (state->mode) {
            state->object = func_080E05DC(state->object);
            if (state->object == 0)
                request->phase = 0x104;
        } else {
            state->object = func_080E05DC(state->object);
            if (state->object == 0) {
                state->task4 = func_080DFD68(1, 30, owner);
                request->phase++;
            }
        }
        break;
    case 0x101:
        state->task4 = func_080DFED8(state->task4);
        if (state->task4 == 0) {
            /* The ROM passes this descriptor without initialising it. */
            state->task0 = func_08005B6C(func_0810EA78, 20, &first, owner);
            request->phase++;
        }
        break;
    case 0x102:
        state->task0 = func_080E051C(state->task0);
        if (state->task0 != 0)
            break;
        second.argument = state->argument;
        state->task1 = func_08005B6C(func_0810EF0C, 488, &second, owner);
        request->phase++;
    case 0x103:
        state->task1 = func_080E051C(state->task1);
        if (state->task1 == 0)
            request->phase++;
        break;
    case 0x104:
        third.x = state->x;
        third.y = state->y;
        third.argument = state->argument;
        state->task2 = func_08005B6C(func_0810FAF8, 344, &third, owner);
        request->phase++;
        break;
    case 0x105:
        state->task2 = func_080E051C(state->task2);
        if (state->task2 == 0) {
            state->task3 = func_08115AE4(state->argument, 0, owner);
            request->phase++;
        }
        break;
    case 0x106:
        state->task3 = func_08115B40(state->task3);
        if (state->task3 == 0)
            request->phase = 2;
        break;
    }
    return 0;
}
