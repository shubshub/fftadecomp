#include "ffta.h"
#include "effect_task.h"

typedef struct {
    u16 phase;
    u16 unknown2;
    void *actor;
    u8 unknown8[14];
    u16 mode;
} SequenceCommand;

typedef struct {
    u8 mode;
    u8 unknown1[3];
    void *object;
    void *actor;
    void *wait;
    u8 effect_data[4];
    void *first;
    void *second;
    void *third;
} SequenceState;

extern const u8 data_0839C464[];
extern const u8 data_0839C47C[];
extern const u8 data_0839C494[];
extern const u8 data_0839C4A8[];
extern void func_080D38B4(void);
extern u8 func_080D3B54(void *actor);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 kind, u16 value,
                          void *output, const void *data, void *task);
extern void *func_080D6134(void *task);
extern u8 func_080D8858(void *actor, u16 flags);
extern void *func_080DBA5C(void *task);
extern void func_080DBDC8(const void *object, s16 *x, s16 *y);

extern u32 func_080DD47C(void *actor);
extern void *func_080DD4A4(void *actor, u8 index);
extern void func_080DE10C(void *object, u16 command);
extern void func_080DE3BC(void *object, u8 enabled);
extern void *func_080DFD8C(const void *data, u8 kind, u16 flags, u16 value,
                          void *task);
extern void *func_080E03F8(void *actor, const void *data, u8 mode, u8 kind,
                          u16 value, void *task);
extern void *func_080E05DC(void *task);

u32 func_080F93E0(void *task, SequenceCommand *command, SequenceState *state)
{
    s16 x, y;

    switch (command->phase) {
    case 0: {
        u8 mode;
        state->mode = command->mode;
        state->actor = command->actor;
        mode = 2;
        if (state->mode != 0)
            mode = 0;
        state->wait = func_080E03F8(state->actor, data_0839C464,
                                   mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->wait = func_080E05DC(state->wait);
        if (state->wait != 0)
            break;
        if (func_080D3B54(state->actor)) {
            command->phase = 2;
            break;
        }
        state->object = (void *)func_080DD47C(state->actor);
        func_080DE10C(state->object, 0x24);
        func_080DE3BC(state->object, 1);
        func_080DBDC8(state->object, &x, &y);
        state->first = func_080D6098(x, y, 0, 1, 1, state->effect_data,
                                    data_0839C47C, task);
        state->third = func_080DFD8C(data_0839C4A8, 2, 4, 0, task);
        command->phase++;
        break;
    case 0x101:
        if (!func_080D8858(state->actor, 0)) {
            command->phase = 2;
            break;
        }
        state->first = func_080D6134(state->first);
        if (state->first == 0) {
            state->second = func_080DCFE4(func_080DD4A4(state->actor, 0),
                                         data_0839C494, 12, 0, 4, task, 0);
            command->phase++;
        }
        break;
    case 0x102:
        state->second = func_080DBA5C(state->second);
        if (state->second == 0)
            command->phase = 2;
        break;
    }
    return 0;
}
