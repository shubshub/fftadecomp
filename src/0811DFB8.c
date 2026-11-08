#include "ffta.h"

/* 0x0811DFB8 .. 0x0811E032: 122 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
    u32 unknown_18;
} EffectCommand;

typedef struct EffectState EffectState;
typedef u32 (*EffectCallback)(void *, EffectCommand *, EffectState *);

typedef struct {
    void *object;
    void *effect;
} ControllerState;

extern void func_080D35D8(void);
extern void *func_08005B6C(EffectCallback, u16, EffectCommand *, void *);
extern void *func_080E051C(void *);
extern u32 func_080E5F50(void *, EffectCommand *, EffectState *);

u32 func_0811DFB8(void *task, EffectCommand *command, ControllerState *state)
{
    EffectCommand request;

    switch (command->state) {
    case 0:
        state->object = command->object;
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        request.kind = 0x18B;
        request.option = 0;
        request.object = state->object;
        state->effect = func_08005B6C(func_080E5F50, 0x40, &request, task);
        command->state++;
        break;
    case 0x101:
        state->effect = func_080E051C(state->effect);
        if (state->effect == 0)
            command->state = 2;
        break;
    }
    return 0;
}
