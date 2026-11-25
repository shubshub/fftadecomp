#include "ffta.h"

/* Complete [0x080B0510, 0x080B0E76): 2406 bytes, including the six-entry
 * jump table at 0x080B0768 and the middle literals. */

/* The C library abs(), which agbcc expands inline (subs; cmp; bge; rsbs). */
extern int abs(int);

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
    u32 *attachment;
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

/* The MotionState of src/08007AD0.c. */
typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} Homing;

/* The record of src/080A9B00.c. */
typedef struct {
    const void *graphics;
    u8 unknown_04[0xC];
    Homing homing;
    u16 axis;
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_34[4];
    u16 angle;
    u16 value_3A;
    u16 value_3C;
    u8 unknown_3E[0x12];
} Trail;

typedef struct {
    Actor *actor;
    Motion motion;
    Motion actor_motion;
    u8 unknown_1C[0x1A];
    u16 animation;
    u8 unknown_38[6];
    s8 direction;
    s8 count;
    u8 flags;
    u8 unknown_41[3];
    Trail trail;
    u8 unknown_94[0x60];
    s16 effect_x;
    s16 effect_y;
    s16 effect_z;
    u8 unknown_FA[2];
    u8 effect_flag;
    u8 effect_flag2;
    u8 unknown_FE[2];
    Transition transition;
    u8 unknown_108[4];
    u32 *attachment;
    s8 heading;
    u8 unknown_111[0x21];
    s8 step_x;
    s8 step_z;
    u8 unknown_134[2];
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
} State;

/* Heading turn for each direction, added to the 16-step heading. */
extern const s8 data_08394581[4];

extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_080A9B00(Trail *trail);
extern void func_08007AD0(Homing *homing);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern u8 func_080A9E6C(State *state, s32 distance);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_0809A09C(Actor *actor);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u16 func_08021C8C(const void *object);
extern u32 func_08021E60(const void *object);
extern const void *func_08021DA8(const void *object, u8 *flip_x, u8 *flip_y);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);

u32 func_080B0510(State *state, Actor *target, void *task, void *effect)
{
    s8 left;
    s8 right;
    u8 flip_x;
    u8 flip_y;

    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 6;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    if (state->flags & 8) {
        u16 dx;
        u16 dz;

        dx = abs(state->actor->x - target->x);
        /* dz is never read.  The ROM keeps its loads and subtraction
         * (0x080B0596-0x080B059E, again at 0x080B0A96 and 0x080B0BD6): the
         * abs() whose test and negation were removed as unused. */
        dz = abs(state->actor->z - target->z);
        state->trail.homing.target_y = target->y << 8;
        if (dx != 0) {
            state->trail.homing.target_x = target->x << 8;
            state->trail.axis |= 2;
        } else {
            state->trail.homing.target_x = target->z << 8;
            state->trail.axis &= ~2;
        }
        state->trail.angle = state->heading << 12;
        state->trail.homing.turn_percent = 100;
        if ((state->heading & 7) == 0)
            state->trail.homing.turn_percent = 102;
        state->heading = (state->heading + data_08394581[state->direction]) & 15;
        func_080A9B00(&state->trail);
        func_08007AD0(&state->trail.homing);
        state->trail.y = state->trail.homing.current_y >> 8;
        if (state->trail.axis & 2)
            state->trail.x = state->trail.homing.current_x >> 8;
        else
            state->trail.z = state->trail.homing.current_x >> 8;
        if (abs(target->x - state->trail.x) + abs(target->z - state->trail.z)
            + abs(target->y - state->trail.y) < 32) {
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            state->flags |= 0x10;
            state->motion.velocity = 0x100;
            state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
            state->effect_y = target->y + (s16)func_08002804() % 41;
            state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
            state->effect_flag = 1;
            state->effect_flag2 = 1;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->flags &= ~0xC;
        }
    }

    switch (state->phase) {
    case 0:
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x * 3) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z * 3) << 5) + 16;
        state->step_x *= -1;
        state->step_z *= -1;
        state->actor->y = target->y;
        func_0809836C(state->actor, 6, state->direction, state->animation);
        func_0809A570(state->actor, 0, 0x1000);
        state->count = 0;
        state->phase = 1;
        break;
    case 1:
        if (func_08099C34(state->actor) != 0)
            break;
        func_0809836C(target, 5, target->direction, 0);
        func_0809A570(target, 0, 0x8000);
        func_080A8390(state->actor->direction, target->direction, &left, &right);
        if (left != 0)
            func_0809A570(target, 0, 0x200);
        if (right != 0)
            func_0809A570(target, 0, 0x400);
        state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
        state->effect_y = target->y + (s16)func_08002804() % 41;
        state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
        state->effect_flag = 1;
        state->effect_flag2 = 1;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->flags |= 0x10;
        func_08141520(0x89);
        state->motion.destination =
            func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
        state->motion.height = target->y << 8;
        state->motion.velocity = 0xA00;
        state->actor_motion.destination = state->actor->y << 8;
        state->actor_motion.height = state->actor->y << 8;
        state->actor_motion.velocity = 0x600;
        state->flags |= 2;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        func_0809A570(state->actor, 0, 0x1000);
        state->phase = 2;
        break;
    case 2: {
        Motion *motion;
        u16 dx;
        u16 dz;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        motion = &state->actor_motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
        state->actor->y = state->actor_motion.height >> 8;
        func_080A9E6C(state, 4);
        if (func_08099C34(state->actor) != 0)
            break;
        state->attachment = state->actor->attachment;
        state->actor->attachment = 0;
        state->trail.value_3A = func_08021C8C(state->attachment);
        state->trail.value_3C = func_08021E60(state->attachment);
        state->trail.graphics = func_08021DA8(state->attachment, &flip_x, &flip_y);
        state->trail.angle = 0;
        state->trail.x = state->actor->x;
        state->trail.y = state->actor->y;
        state->trail.z = state->actor->z;
        dx = abs(state->actor->x - target->x);
        dz = abs(state->actor->z - target->z);
        state->trail.axis |= 1;
        state->trail.homing.target_y = target->y << 8;
        state->trail.homing.current_y = state->actor->y << 8;
        if (dx != 0) {
            state->trail.homing.target_x = target->x << 8;
            state->trail.homing.current_x = state->actor->x << 8;
            state->trail.axis |= 2;
        } else {
            state->trail.homing.target_x = target->z << 8;
            state->trail.homing.current_x = state->actor->z << 8;
            state->trail.axis &= ~2;
        }
        state->trail.homing.speed = 1;
        state->trail.homing.turn_percent = 100;
        func_08007AD0(&state->trail.homing);
        state->trail.homing.turn_percent = 5;
        state->trail.homing.speed = 0xC00;
        state->heading = 0;
        func_08021DE4(state->attachment, 0x40, 0x100);
        func_0809A570(state->actor, 0, 0x100);
        func_08141520(0x122);
        state->flags |= 0xC;
        state->phase = 3;
        break;
    }
    case 3: {
        Motion *motion;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
        if ((state->flags & 0xC) == 0)
            state->phase = 4;
        break;
    }
    case 4: {
        Motion *motion;
        u16 dx;
        u16 dz;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
        dx = abs(state->actor->x - target->x);
        dz = abs(state->actor->z - target->z);
        state->actor->x += state->step_x * 4;
        state->actor->z += state->step_z * 4;
        switch (state->actor->direction) {
        case 0:
        case 2:
            state->effect_x = state->actor->x - state->step_x * 32;
            state->effect_y = state->actor->y + 8;
            state->effect_z = state->actor->z - state->step_z * 32;
            state->effect_flag = 6;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            break;
        case 1:
        case 3:
            state->effect_x = state->actor->x - state->step_x * 32;
            state->effect_y = state->actor->y + 8;
            state->effect_z = state->actor->z - state->step_z * 32;
            state->effect_flag = 5;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            break;
        }
        if (++state->count > 7) {
            func_0809A570(state->actor, 0x100, 0);
            state->phase = 5;
        } else {
            state->trail.homing.target_y = target->y << 8;
            state->trail.homing.current_y = state->actor->y << 8;
            if (dx != 0) {
                state->trail.homing.target_x = target->x << 8;
                state->trail.homing.current_x = state->actor->x << 8;
                state->trail.axis |= 2;
            } else {
                state->trail.homing.target_x = target->z << 8;
                state->trail.homing.current_x = state->actor->z << 8;
                state->trail.axis &= ~2;
            }
            state->flags |= 0xC;
            state->phase = 3;
            func_08141520(0xDF);
        }
        break;
    }
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
            state->actor->attachment = state->attachment;
            func_0809A09C(state->actor);
            func_0809836C(target, 5, target->direction, 0);
            state->actor->flags |= 1;
            state->flags &= ~2;
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 2;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            return 0;
        }
        break;
    }
    }
    return 1;
}
