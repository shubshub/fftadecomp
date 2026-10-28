#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} Entity;

typedef struct {
    Entity *entity;
} EntityHolder;

typedef struct {
    u8 step;
    u8 flags;
} StepState;

extern s32 func_08098BB0(EntityHolder *holder, StepState *state);

/* 0x0809AD48..0x0809AD6C: 36 bytes. */
s32 func_0809AD48(EntityHolder *holder, StepState *state)
{
    s32 result;

    if (holder->entity->flags & 0x4000)
        result = func_08098BB0(holder, state);
    else
        result = 1;
    return result;
}
