#include "ffta.h"

typedef struct Entity Entity;

typedef struct {
    Entity *entity;
} EntityHolder;

typedef struct {
    u8 step;
    u8 flags;
} StepState;

extern u8 func_080C8280(Entity *entity);
extern u8 func_080CD8CC(Entity *entity);
extern u8 func_080CD92C(Entity *entity);
extern u8 func_080CDCEC(Entity *entity);
extern u8 func_080C8260(Entity *entity);
extern u8 func_080C84C0(Entity *entity);

u8 func_08098BB0(EntityHolder *holder, StepState *state)
{
    if (func_080C8280(holder->entity) && !func_080CD8CC(holder->entity))
        return 1;
    if (func_080CD92C(holder->entity))
        return 1;
    if (func_080CDCEC(holder->entity))
        return 1;
    if ((state->flags & 1) && func_080C8260(holder->entity))
        return 1;
    if ((state->flags & 2) && !func_080C84C0(holder->entity))
        return 1;
    state->step++;
    return 1;
}
