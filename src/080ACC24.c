#include "ffta.h"

/* Complete [0x080ACC24, 0x080AD166): 1346 bytes, including middle literals. */

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
    Motion target_motion;
    u8 unknown_1C[0x1A];
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
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u32 func_08099C64(const Actor *actor);

u32 func_080ACC24(State *state, Actor *target, void *task, void *effect)
{
    s8 left;
    s8 right;

    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 8;
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
        state->destination_x = (((target->x >> 5) - state->step_x * 3) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z * 3) << 5) + 16;
        /* src/080AB358.c's text: the ROM sign-extends each step before
         * negating it (ldrsb at 0x080ACD3C and 0x080ACD44). */
        state->step_x *= -1;
        state->step_z *= -1;
        state->motion.destination = target->y << 8;
        state->motion.height = (target->y - 0x30) << 8;
        state->motion.velocity = 0x600;
        state->actor->y = state->motion.height >> 8;
        state->target_motion.destination = target->y << 8;
        state->target_motion.height = target->y << 8;
        state->target_motion.velocity = 0;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        state->count = 8;
        state->phase = 1;
        break;
    case 1: {
        Motion *motion;

        motion = &state->target_motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->target_motion.height >> 8;
        func_080A9E6C(state, 4);
        if (func_08099C34(state->actor) == 0) {
            func_08141520(0x80);
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            func_080A8390(state->actor->direction, target->direction, &left, &right);
            if (left != 0)
                func_0809A570(target, 0, 0x200);
            if (right != 0)
                func_0809A570(target, 0, 0x400);
            state->effect_x = target->x + func_08142950((s16)func_08002804(), 33) - 16;
            state->effect_y = target->y + func_08142950((s16)func_08002804(), 33);
            state->effect_z = target->z + func_08142950((s16)func_08002804(), 33) - 16;
            state->effect_flag = 1;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 2;
            state->effect_flag2 = 3;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->destination_x += state->step_x * 8;
            state->destination_z += state->step_z * 8;
            state->target_motion.destination =
                func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
            state->count--;
            state->flags |= 0x10;
            /* The first hit tests the count before this decrement,
             * count + 1, as src/080ABBD8.c tests its count; the ROM reads
             * count afresh for the second test (0x080ACF88) instead of
             * reusing the value compared at 0x080ACF68. */
            if (state->count + 1 == 8) {
                state->target_motion.velocity = 0xA19;
                func_0809836C(state->actor, 7, state->direction, state->animation);
            } else if (state->count != 0) {
                state->flags &= ~2;
                func_0809836C(state->actor, 7, state->direction, state->animation);
                func_0809A570(state->actor, 0, 0x2000);
                state->target_motion.velocity = 0x500;
            }
        }
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->y = state->motion.height >> 8;
        if (func_08099C64(state->actor)) {
            func_0809836C(state->actor, 3, state->direction, 0);
            state->motion.destination = (state->actor->y - 0x30) << 8;
            state->motion.height = state->actor->y << 8;
            state->motion.velocity = 0x800;
            state->actor->y = state->motion.height >> 8;
            state->count = 1;
            state->phase = 2;
        }
        break;
    }
    case 2: {
        Motion *motion;
        s32 moving;
        s32 target_moving;

        if (state->step_x)
            state->actor->x += state->step_x * 4;
        if (state->step_z)
            state->actor->z += state->step_z * 4;
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0) {
            motion->height = motion->destination;
            moving = 0;
        } else {
            moving = 1;
        }
        state->actor->y = state->motion.height >> 8;
        motion = &state->target_motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0) {
            motion->height = motion->destination;
            target_moving = 0;
        } else {
            target_moving = 1;
        }
        if (target_moving != state->count) {
            func_0809836C(target, 5, target->direction, 0);
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 2;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_08141520(0x89);
            state->count = target_moving;
        }
        target->y = state->target_motion.height >> 8;
        if (!moving) {
            state->actor->flags |= 1;
            if (!target_moving) {
                state->flags = 0;
                return 0;
            }
        }
        break;
    }
    }
    return 1;
}
