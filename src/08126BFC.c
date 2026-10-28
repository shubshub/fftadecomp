#include "ffta.h"

/* 0x08126BFC..0x08126D32: 310 bytes, 143 reachable instructions. */
typedef struct {
    u8 unknown_00[0xF8];
    u8 direction;
} ObjectData;

typedef struct {
    ObjectData *data;
    u8 unknown_04[0x2C];
    u32 flags;
} SceneObject;

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} EffectOwner;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    EffectOwner *owner;
    u8 unknown_08[0xC];
    u8 index;
    u8 unknown_15;
    u16 destination;
    u16 alternate;
} EffectCommand;

typedef struct {
    EffectOwner *owner;
    SceneObject *object;
    u8 current;
    u8 destination;
    u8 timer;
    u8 alternate;
} EffectState;

extern ObjectData *func_08125578(u8);
extern void *func_08096D7C(EffectOwner *);
extern SceneObject *func_08099560(void *, ObjectData *);
extern void func_0809836C(SceneObject *, u32, s8, u32);
extern void func_08124710(SceneObject *, u32, u8);

u32 func_08126BFC(void *task, EffectCommand *command, EffectState *state)
{
    switch (command->phase) {
    case 0:
    {
        ObjectData *data = func_08125578(command->index);
        s32 difference;

        state->owner = command->owner;
        state->object = func_08099560(func_08096D7C(state->owner), data);
        state->current = data->direction;
        state->destination = command->destination;
        state->timer = 6;
        state->alternate = command->alternate;
        if (state->current > state->destination) {
            difference = state->current - state->destination;
            state->current--;
        } else {
            difference = state->destination - state->current;
            state->current++;
        }
        if (difference != 2)
            state->current = state->destination;
        if (!state->alternate || (state->object->flags & 4)) {
            func_0809836C(state->object, 1, (s8)state->current, 0);
            state->object->data->direction = state->current;
            func_08124710(state->object, 0, state->current);
        } else {
            func_08124710(state->object, 1, state->current);
        }
        break;
    }
    case 1:
        break;
    case 0x100:
        if (state->timer) {
            state->timer--;
            break;
        }
        if (state->current != state->destination) {
            if (!state->alternate || (state->object->flags & 4)) {
                func_0809836C(state->object, 1, (s8)state->destination, 0);
                state->object->data->direction = state->destination;
                func_08124710(state->object, 0, state->destination);
            } else {
                func_08124710(state->object, 1, state->destination);
            }
            state->current = state->destination;
            state->timer = 6;
        } else {
            command->phase = 0x101;
        }
        break;
    case 0x101:
        state->owner->complete = 1;
        command->phase = 3;
        break;
    }
    return 0;
}
