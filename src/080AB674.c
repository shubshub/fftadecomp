#include "ffta.h"

/* Complete [0x080AB674, 0x080ABBD8): 1380 bytes, including the 11-word
 * phase jump table at 0x080AB6F0 and the middle literals. */

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
    u8 unknown_24[0x1A];
    s8 direction;
    u8 unknown_3F;
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
    s16 counter;
    u8 unknown_138[4];
    u16 phase;
} State;

extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern void func_0809A298(Actor *actor, u16 value, s8 adjustment);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);

u32 func_080AB674(State *state, Actor *target, void *task, void *effect)
{
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
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x * 4) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z * 4) << 5) + 16;
        state->actor->y = target->y;
        func_0809836C(state->actor, 4, state->direction, 0);
        state->counter = 0;
        state->phase = 1;
        func_08141520(0xDD);
        break;
    case 1:
        state->timer = 8;
        state->actor->flags ^= 1;
        state->effect_x = state->actor->x;
        state->effect_y = state->actor->y;
        state->effect_z = state->actor->z;
        state->effect_flag = state->counter + 5;
        state->effect_flag2 = 0;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->counter++;
        state->phase = 2;
        break;
    case 2:
        state->actor->flags ^= 1;
        if (--state->timer <= 0) {
            if (state->counter > 2) {
                state->timer = 0x30;
                state->actor->flags &= ~1;
                state->phase = 3;
            } else {
                state->phase = 1;
            }
        }
        break;
    case 3:
        if (--state->timer <= 0) {
            func_0809A298(state->actor, 0x3C, state->direction);
            state->phase = 4;
        }
        break;
    case 4:
        if (func_08099C34(state->actor) >= 0) {
            func_0809A570(state->actor, 0, 0x100);
            func_08141520(0x101);
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y + 0x20;
            state->effect_z = state->actor->z;
            state->effect_flag = 4;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->timer = 0x40;
            state->phase = 6;
        }
        break;
    case 6:
        if (--state->timer <= 0) {
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 7;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->timer = 0x20;
            func_08141520(0x106);
            state->phase = 7;
        }
        break;
    case 7:
        if (--state->timer <= 0) {
            func_0809A570(state->actor, 0x100, 0);
            state->motion.destination =
                func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
            state->motion.height = target->y << 8;
            state->timer = 0;
            state->counter = 8;
            state->phase = 8;
        }
        break;
    case 8: {
        Motion *motion;

        if (state->timer == 0) {
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            state->effect_x = target->x - (s16)func_08002804() % 33;
            /* The ROM adds 8 to the remainder (0x080AB9F8) and then loads
             * and adds target->y (0x080AB9FC-0x080AB9FE), with no sign
             * extension between the call and the store, as for the same
             * step in src/080AB358.c (divisor 9). */
            state->effect_y = (s16)((s16)func_08002804() % 33 + 8) + target->y;
            state->effect_z = target->z - (s16)func_08002804() % 33;
            state->effect_flag = 1;
            state->effect_flag2 = 4;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->counter--;
            state->flags |= 0x10;
            func_08141520(0x7B);
            if (state->counter <= 0) {
                state->phase = 9;
                state->counter = -1;
                state->timer = 0;
                break;
            }
            state->motion.velocity = 0x400;
        }
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
        state->timer = (state->timer + 1) & 7;
        break;
    }
    case 9: {
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
            func_0809836C(target, 5, target->direction, 0);
            func_08141520(0x8B);
            state->phase = 10;
        }
        /* Falls through: while it is still moving the ROM branches to
         * case 10's body at 0x080ABB18 (bne at 0x080ABAF6), and the landing
         * path's phase store (0x080ABB16) runs into it. */
    }
    case 10:
        if (state->counter <= 2) {
            state->actor->flags ^= 1;
            if (state->timer == 0) {
                state->timer = 8;
                state->effect_x = state->actor->x;
                state->effect_y = state->actor->y;
                state->effect_z = state->actor->z;
                state->effect_flag = state->counter + 5;
                state->effect_flag2 = 0;
                func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                              state->effect_flag, state->effect_flag2);
                state->counter++;
                if (state->counter > 2)
                    state->actor->flags |= 1;
            } else {
                state->timer--;
            }
        }
        if (state->phase == 10 && state->counter > 2)
            return 0;
        break;
    }
    return 1;
}
