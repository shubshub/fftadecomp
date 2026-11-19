#include "ffta.h"

/* Complete [0x080ABBD8, 0x080AC05A): 1154 bytes, including middle literals. */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u8 unknown_34[0x18];
    u32 *additional_flags;
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
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Position;

typedef struct {
    Actor *actor;
    Motion motion;
    u8 unknown_10[0x26];
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
extern u8 func_0802202C(const u32 *flags);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);
extern u8 func_080A9E6C(State *state, s32 distance);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u32 func_080A83A4(const Position *source, u32 value_08, u32 value_0E,
                         u32 value_0A, u32 value_0C);
extern void func_080A7EC4(u16 command);
extern u32 func_080A83DC(void);
extern u32 func_08099C64(const Actor *actor);

u32 func_080ABBD8(State *state, Actor *target, void *task, void *effect)
{
    s8 left;
    s8 right;
    Position position;

    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 7;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    switch (state->phase) {
    case 0:
        state->flags |= 2;
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x * 4) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z * 4) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->motion.destination = target->y << 8;
        state->motion.height = (target->y - 32) << 8;
        state->motion.velocity = 0x900;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        state->count = 0;
        state->phase = 1;
        break;
    case 1: {
        Motion *motion;
        s32 moving;
        s32 height_offset;

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
        if (state->actor->additional_flags != 0
            && func_0802202C(state->actor->additional_flags))
            func_08021DE4(state->actor->additional_flags, 0, 0x40);
        func_080A9E6C(state, 4);
        if (moving)
            break;
        if (func_08099C34(state->actor) != 0)
            break;
        state->flags &= ~2;
        func_0809836C(target, 5, target->direction, 0);
        func_0809A570(target, 0, 0x8000);
        func_080A8390(state->actor->direction, target->direction, &left, &right);
        if (left != 0)
            func_0809A570(target, 0, 0x200);
        if (right != 0)
            func_0809A570(target, 0, 0x400);
        state->effect_x = target->x
            - state->step_x * func_08142950((s16)func_08002804(), 17);
        /* The ROM adds 8 to the remainder (0x080ABE36) before it adds
         * target->y (0x080ABE38-0x080ABE3A); src/080A9F24.c spells the same
         * step this way. */
        height_offset = func_08142950((s16)func_08002804(), 17) + 8;
        state->effect_y = target->y + height_offset;
        state->effect_z = target->z
            - state->step_z * func_08142950((s16)func_08002804(), 17);
        state->effect_flag = 1;
        state->effect_flag2 = 0;
        /* The arguments are the fields just stored: the ROM reloads the
         * first four (0x080ABE78-0x080ABE86) and gives the last its own
         * zero (0x080ABE8A), apart from the one stored at 0x080ABE74. */
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        if (state->count > 7) {
            func_08141520(0x8B);
            /* The ROM clears 2 a second time (0x080ABEAA; first 0x080ABD98). */
            state->flags &= ~2;
            state->motion.destination =
                func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
            state->motion.height = target->y << 8;
            state->motion.velocity = -0x800;
            state->phase = 2;
            state->count = 0;
            position.y = state->motion.destination >> 8;
            position.x = target->x;
            position.z = target->z;
            func_080A83A4(&position, 8, 1, -0x78, -0x56);
        } else {
            func_080A7EC4(state->animation);
            state->flags |= 0x10;
            func_0809836C(state->actor, 7, state->direction, state->animation);
            if (state->count + 1 < 8 && state->count != 0) {
                func_0809A570(state->actor, 0, 0x2000);
                if (state->actor->additional_flags != 0)
                    func_08021DE4(state->actor->additional_flags, 0x40, 0);
            }
            state->count++;
        }
        break;
    }
    case 2: {
        Motion *motion;
        s32 moving;
        u32 pending;

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
        pending = func_080A83DC();
        if (!moving && state->count == 0) {
            state->count = 1;
            func_08141520(0x89);
            func_0809836C(target, 5, target->direction, 0);
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 2;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
        }
        if (func_08099C64(state->actor) && !moving && !pending) {
            state->actor->flags |= 1;
            state->flags = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}
