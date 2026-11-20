// Target: complete [0x0811C2E8, 0x0811C50C), 548 bytes including literals.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u8 kind;
} Command0811C2E8;

typedef struct {
    s16 current;
    s16 unknown_02[5];
} Motion0811C2E8;

typedef struct {
    u8 index;
    u8 unknown_01;
    u16 timer;
    s16 x;
    s16 y;
    void *object;
    void *effect;
    Motion0811C2E8 first;
    Motion0811C2E8 second;
    void *task;
    void *sprite;
} State0811C2E8;

typedef struct {
    s16 x;
    s16 y;
} Point0811C2E8;

extern const Point0811C2E8 data_083A6C18[];
extern const u8 data_0894DD84[];
extern const u8 data_083A6C10[];

extern void func_080D35D8(void);
extern void *func_080DC1E8(void *, u8, u8, u8, void *, void *, void *);
extern void *func_080DBA5C(void *);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern u16 func_080035A8(u8 layer);
extern void func_0801C960(s16 x, s16 y, s16 *first, s16 *second);
extern void func_080DC224(void *, s16, s16, s16 *, s16 *);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080E0608(Motion0811C2E8 *, s16, s16, s16);
extern void func_080E064C(Motion0811C2E8 *);
extern u8 func_080E0690(Motion0811C2E8 *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void func_080D4020(void);
extern void func_080DBEB4(void *, u8);

int func_0811C2E8(void *owner, Command0811C2E8 *command, State0811C2E8 *state)
{
    s16 x;
    s16 y;
    s16 target_x;
    s16 target_y;

    switch (command->phase) {
    case 0:
        state->index = command->kind - 0x78;
        state->object = command->object;
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        state->task = func_080DC1E8(state->object, 0, 0, 6,
            (void *)0x0600F9E0, (void *)0x06005000, owner);
        command->phase++;
        break;
    case 0x101:
        state->task = func_080DBA5C(state->task);
        if (state->task)
            break;
        func_080034B8(func_08003A74(0x06005000) | func_08003A80(0x06008000), 3);
        g_control_flags_03000940.display |= func_080035A8(3);
        func_0801C960(data_083A6C18[state->index].x,
            data_083A6C18[state->index].y, &x, &y);
        func_080DC224(state->object, x, y, &x, &y);
        y += 8;
        func_08003508(x, 3);
        func_08003558(y, 3);
        func_080DBDC8(state->object, &state->x, &state->y);
        func_080DC224(state->object, state->x, state->y, &target_x, &target_y);
        func_080E0608(&state->first, x, target_x, 90);
        func_080E0608(&state->second, y, target_y, 90);
        state->effect = func_080D3E9C(data_0894DD84, owner);
        state->sprite = func_080DFD8C(data_083A6C10, 1, 4, 0, owner);
        state->timer = 40;
        command->phase++;
        break;
    case 0x102:
        if (state->timer && --state->timer)
            break;
        func_080E064C(&state->first);
        func_080E064C(&state->second);
        func_08003508(state->first.current, 3);
        func_08003558(state->second.current, 3);
        if (func_080E0690(&state->first)) {
            state->timer = 40;
            command->phase++;
        }
        break;
    case 0x103:
        if (state->timer && --state->timer)
            break;
        state->effect = func_080D3F08(state->effect);
        if (state->effect)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        func_080D4020();
        func_080DBEB4(state->object, 1);
        command->phase = 2;
        break;
    }
    return 0;
}
