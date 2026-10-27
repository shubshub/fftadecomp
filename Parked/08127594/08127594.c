#include "ffta.h"

/* 0x08127594..0x081276D6: 322 bytes, including the literal pool. */
typedef struct {
    s16 current;
    s16 unknown_02;
    s16 target;
    u8 unknown_06[0x12];
} MovementAxis;

typedef struct {
    u8 unknown_00[6];
    u8 finished;
} MovementOwner;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 height;
    s16 y;
} MovingEntity;

typedef struct {
    MovementOwner *owner;
    MovingEntity *entity;
    u8 unknown_08[7];
    u8 facing;
    s8 direction_x;
    s8 direction_y;
    s16 tile_x;
    s16 tile_height;
    s16 tile_y;
    MovementAxis x;
    MovementAxis y;
} MovementState;

extern void func_080076F4(MovementAxis *);
extern int func_08007894(MovementAxis *);
extern u8 func_0801CC18(u8, u8);
extern int func_08127380(MovementState *);
extern void func_081277C8(MovementState *);
extern void func_0809A530(MovingEntity *, u8);
extern void func_0809A570(MovingEntity *, int, int);

static inline u8 update_facing(MovementState *state)
{
    int facing = func_08127380(state);
    if (facing != state->facing) {
        state->facing = facing;
        return 1;
    }
    return 0;
}

u32 func_08127594(MovementState *state)
{
    u32 result = 0x101;
    int old_x;
    int old_y;
    int delta_x;
    int delta_y;
    int done_x;
    int done_y;

    func_080076F4(&state->x);
    old_x = state->entity->x;
    func_080076F4(&state->y);
    old_y = state->entity->y;
    state->entity->x = state->x.current;
    state->entity->y = state->y.current;
    delta_x = state->entity->x - old_x + state->direction_x * 15;
    delta_y = state->entity->y - old_y + state->direction_y * 15;
    if ((old_x >> 5) == (state->x.target >> 5))
        delta_x = 0;
    if ((old_y >> 5) == (state->y.target >> 5))
        delta_y = 0;
    state->tile_x = (old_x + delta_x) >> 5;
    state->tile_y = (old_y + delta_y) >> 5;
    if (state->tile_x < 0)
        state->tile_x = 0;
    if (state->tile_y < 0)
        state->tile_y = 0;
    state->tile_height = func_0801CC18(state->tile_x, state->tile_y);
    if ((state->tile_height << 4) == state->entity->height) {
        if (update_facing(state))
            func_0809A530(state->entity, state->facing);
    } else {
        func_081277C8(state);
        result = 0x102;
    }

    done_x = func_08007894(&state->x);
    done_y = func_08007894(&state->y);
    if (done_x && done_y) {
        state->entity->height = func_0801CC18(state->entity->x >> 5,
                                           state->entity->y >> 5) * 16;
        func_0809A570(state->entity, 0, 0x100);
        state->owner->finished = 1;
        result = 3;
    }
    return result;
}
