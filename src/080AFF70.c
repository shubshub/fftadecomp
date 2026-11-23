#include "ffta.h"

/* Complete [0x080AFF70, 0x080B050E): 1438 bytes, including the six-entry
 * jump table at 0x080AFFEC and the middle literals. */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
} Actor;

typedef struct {
    s32 velocity;
    s32 height;
    s32 destination;
} Motion;

typedef struct {
    u16 first;
    u16 second;
    u16 third;
    u8 level;
} Transition;

typedef struct {
    Actor *actor;
    Motion motion;
    u8 unknown_10[0x12];
    s16 timer;
    u8 unknown_24[0x12];
    u16 animation;
    u8 unknown_38[6];
    s8 direction;
    s8 count;
    u8 flags;
    u8 unknown_41[0xB3];
    s16 effect_x;
    s16 effect_y;
    s16 effect_z;
    u8 unknown_FA[2];
    u8 effect_flag;
    u8 effect_flag2;
    u8 unknown_FE[2];
    Transition transition;
    u8 unknown_108[0x2A];
    s8 step_x;
    s8 step_z;
    u8 unknown_134[2];
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
} State;

extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern u8 func_080A9E6C(State *state, s32 distance);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_0809A09C(Actor *actor);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);

u32 func_080AFF70(State *state, Actor *target, void *task, void *effect)
{
    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 12;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    switch (state->phase) {
    case 0:
        state->flags |= 2;
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x * 4) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z * 4) << 5) + 16;
        state->step_x *= -1;
        state->step_z *= -1;
        state->motion.destination = target->y << 8;
        state->motion.height = (target->y - 0x30) << 8;
        state->motion.velocity = 0x800;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        state->phase = 1;
        break;
    case 1: {
        Motion *motion;

        if (func_08099C34(state->actor) == 0) {
            func_08141520(0xEB);
            func_0809A570(state->actor, 0, 0x100);
            state->timer = 0;
            state->effect_x = state->actor->x - state->step_x * 32;
            state->effect_y = state->actor->y + 16;
            state->effect_z = state->actor->z - state->step_z * 32;
            state->effect_flag = 4;
            state->effect_flag2 = 5;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->phase = 2;
        }
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->y = state->motion.height >> 8;
        func_080A9E6C(state, 4);
        break;
    }
    case 2:
        if (state->timer < 0x40) {
            if (state->timer == 0x10) {
                state->effect_x = state->actor->x - state->step_x * 32;
                state->effect_y = state->actor->y + 16;
                state->effect_z = state->actor->z - state->step_z * 32;
                state->effect_flag = 7;
                state->effect_flag2 = 5;
                func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                              state->effect_flag, state->effect_flag2);
            }
            state->timer++;
        } else {
            state->timer = 0;
            state->count = 0;
            state->phase = 3;
        }
        break;
    case 3:
        if (++state->count > 7) {
            s16 x;
            s16 y;
            s16 z;

            /* The position is read before the timer advances and the random
             * calls, and stored after them (0x080B025E, 0x080B02CE). */
            state->count = 0;
            x = state->actor->x;
            y = state->actor->y;
            z = state->actor->z;
            x -= (state->timer * 32 + 16) * state->step_x;
            z -= (state->timer * 32 + 16) * state->step_z;
            state->timer++;
            y += (s16)func_08002804() % 0x41 - 0x18;
            state->flags |= 0x10;
            func_08141520(0xD4);
            state->effect_x = x;
            state->effect_y = y;
            state->effect_z = z;
            state->effect_flag = 0;
            state->effect_flag2 = (s16)func_08002804() % 6;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            if (state->timer > 3) {
                state->timer = 0;
                state->phase = 4;
            }
        }
        break;
    case 4:
        if (state->timer < 0x28) {
            state->timer++;
        } else {
            func_08141520(0x151);
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            state->effect_x = target->x;
            state->effect_y = target->y + 0x18;
            state->effect_z = target->z;
            state->effect_flag = 0;
            state->effect_flag2 = 1;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 4;
            state->effect_flag2 = 4;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->flags |= 0x10;
            func_0809A09C(state->actor);
            func_0809836C(state->actor, 0, state->actor->direction, 0);
            state->actor->flags |= 1;
            state->flags &= ~2;
            if ((state->flags & 0xC) == 0) {
                state->motion.destination =
                    func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
                state->motion.height = target->y << 8;
                state->motion.velocity = -0x400;
                state->phase = 5;
            }
        }
        break;
    case 5: {
        Motion *motion;
        s32 moving;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0) {
            motion->height = motion->destination;
            moving = 0;
        } else {
            moving = 1;
        }
        target->y = state->motion.height >> 8;
        if (!moving) {
            func_08141520(0x89);
            func_0809836C(target, 5, target->direction, 0);
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 2;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->flags = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}
