#include "ffta.h"

/* Complete [0x080AE7D8, 0x080AF22E): 2646 bytes, including the six-entry
 * jump table at 0x080AEC14 and the middle literals. */

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

/* The steering motion func_08007AD0 (src/08007AD0.c) advances. */
typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} Steering;

/* The thrown object.  func_080A9B00 (src/080A9B00.c) reads its position at
 * +0x2E and its rotation at +0x38. */
typedef struct {
    const void *graphics;
    u8 unknown_04[0xC];
    Steering steering;
    u16 flags;
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_34[4];
    u16 rotation;
    u16 value;
    u16 parameter;
} Projectile;

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
    u8 unknown_41[3];
    Projectile projectile;
    u8 unknown_84[0x70];
    s16 effect_x;
    s16 effect_y;
    s16 effect_z;
    u8 unknown_FA[2];
    u8 effect_flag;
    u8 effect_flag2;
    u8 unknown_FE[2];
    Transition transition;
    u8 unknown_108[4];
    u32 *saved_flags;
    s8 spin;
    u8 unknown_111[0x21];
    s8 step_x;
    s8 step_z;
    u8 unknown_134[2];
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
} State;

/* The spin step for each direction: -1, 1, 1, -1 (literal word 0x080AE8E8). */
extern const s8 data_0839457D[4];

extern s32 abs(s32 value);
extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_08141520(u16 sound);
extern void func_080A9B00(Projectile *projectile);
extern void func_08007AD0(Steering *steering);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_0809A09C(Actor *actor);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern s32 func_08099C34(Actor *actor);
extern u16 func_08021C8C(const void *object);
extern u32 func_08021E60(const void *object);
extern const void *func_08021DA8(const void *object, u8 *flip_x, u8 *flip_y);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);
extern u8 func_080A9E6C(State *state, s32 distance);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u32 func_080A83A4(const Position *source, u32 value_08, u32 value_0E,
                         u32 value_0A, u32 value_0C);
extern u32 func_080A83DC(void);
extern u32 func_08099C64(const Actor *actor);

u32 func_080AE7D8(State *state, Actor *target, void *task, void *effect)
{
    u8 flip_x;
    u8 flip_y;
    s8 left;
    s8 right;
    Position position;
    /* One distance serves both proximity tests (0x080AE90C, 0x080AEB9A). */
    s32 distance;

    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 6;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    if (state->flags & 8) {
        state->projectile.rotation = state->spin << 12;
        if ((state->spin & 7) == 0) {
            state->projectile.steering.turn_percent += 2;
            if (state->projectile.steering.turn_percent > 100)
                state->projectile.steering.turn_percent = 100;
        }
        state->spin = (state->spin + data_0839457D[state->direction]) & 0xF;
        if (state->spin == 0 && state->timer == 0 && state->count <= 1)
            func_08141520(0x85);
        func_080A9B00(&state->projectile);
        func_08007AD0(&state->projectile.steering);
        state->projectile.y = state->projectile.steering.current_y >> 8;
        if (state->projectile.flags & 2)
            state->projectile.x = state->projectile.steering.current_x >> 8;
        else
            state->projectile.z = state->projectile.steering.current_x >> 8;
        if (state->count <= 1) {
            if (state->timer == 0) {
                distance = abs(target->x - state->projectile.x)
                    + abs(target->z - state->projectile.z)
                    + abs(target->y - state->projectile.y);
                if (distance < 32) {
                    state->timer = 8;
                    state->projectile.steering.turn_percent = 1;
                    func_0809836C(target, 5, target->direction, 0);
                    func_0809A570(target, 0, 0x8000);
                    func_08141520(0x7B);
                    if (++state->count > 1) {
                        if (state->projectile.flags & 2)
                            state->projectile.steering.target_x = state->actor->x << 8;
                        else
                            state->projectile.steering.target_x = state->actor->z << 8;
                    }
                    state->flags |= 0x10;
                    state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
                    state->effect_y = target->y + (s16)func_08002804() % 41;
                    state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
                    state->effect_flag = 1;
                    state->effect_flag2 = 1;
                    func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                                  state->effect_flag, state->effect_flag2);
                }
            } else {
                if ((state->timer & 3) == 0 && state->timer <= 7)
                    func_08141520(0x7B);
                if ((state->timer & 1) && state->timer <= 7) {
                    state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
                    state->effect_y = target->y + (s16)func_08002804() % 41;
                    state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
                    state->effect_flag = 1;
                    state->effect_flag2 = 1;
                    func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                                  state->effect_flag, state->effect_flag2);
                    state->flags |= 0x10;
                }
                state->timer--;
            }
        } else {
            if (state->timer != 0) {
                if ((state->timer & 3) == 0 && state->timer <= 7)
                    func_08141520(0x7B);
                if ((state->timer & 1) && state->timer <= 7) {
                    state->flags |= 0x10;
                    state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
                    state->effect_y = target->y + (s16)func_08002804() % 41;
                    state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
                    state->effect_flag = 1;
                    state->effect_flag2 = 1;
                    func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                                  state->effect_flag, state->effect_flag2);
                }
                state->timer--;
            }
            distance = abs(state->actor->x - state->projectile.x)
                + abs(state->actor->z - state->projectile.z)
                + abs(state->actor->y - state->projectile.y);
            if (distance < 32) {
                state->flags &= ~0xC;
                state->actor->additional_flags = state->saved_flags;
                func_0809A09C(state->actor);
            }
        }
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
        state->motion.velocity = 0x900;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        state->count = 0;
        state->phase = 1;
        break;
    case 1:
        if (func_08099C34(state->actor) == 0) {
            u8 dx;
            u8 dz;

            state->saved_flags = state->actor->additional_flags;
            state->actor->additional_flags = 0;
            state->projectile.value = func_08021C8C(state->saved_flags);
            state->projectile.parameter = func_08021E60(state->saved_flags);
            state->projectile.graphics = func_08021DA8(state->saved_flags, &flip_x, &flip_y);
            state->projectile.rotation = 0;
            state->projectile.x = state->actor->x;
            state->projectile.y = state->actor->y;
            state->projectile.z = state->actor->z;
            dx = abs(state->actor->x - target->x);
            /* dz is never read: the ROM keeps its subtraction
             * (0x080AED90-0x080AED98) and drops the rest. */
            dz = abs(state->actor->z - target->z);
            state->projectile.flags |= 1;
            state->projectile.steering.target_y = target->y << 8;
            state->projectile.steering.current_y = state->actor->y << 8;
            if (dx != 0) {
                state->projectile.steering.target_x = target->x << 8;
                state->projectile.steering.current_x = state->actor->x << 8;
                state->projectile.flags |= 2;
            } else {
                state->projectile.steering.target_x = target->z << 8;
                state->projectile.steering.current_x = state->actor->z << 8;
                state->projectile.flags &= ~2;
            }
            state->projectile.steering.speed = 1;
            state->projectile.steering.turn_percent = 100;
            func_08007AD0(&state->projectile.steering);
            state->projectile.steering.turn_percent = 5;
            state->projectile.steering.speed = 0x800;
            state->spin = 0;
            func_08021DE4(state->saved_flags, 0x40, 0x100);
            func_08141520(0x85);
            state->flags |= 0xC;
            state->timer = 0;
            state->count = 0;
            state->phase = 2;
        }
        /* Falls through: phase 1 runs on into the phase 2 code at
         * 0x080AEE48, the jump table's third entry. */
    case 2: {
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
        state->actor->y = state->motion.height >> 8;
        /* The ROM compares with 1 here (0x080AEE7A), not with 0. */
        if (moving == 1) {
            func_080A9E6C(state, 4);
            break;
        }
        if (state->count > 1 && !(state->flags & 8)) {
            func_0809D66C(state->direction, &state->step_x, &state->step_z);
            state->destination_x = (((target->x >> 5) - state->step_x) << 5) + 16;
            state->destination_z = (((target->z >> 5) - state->step_z) << 5) + 16;
            state->motion.destination = target->y << 8;
            state->motion.velocity = 0x800;
            state->actor->y = state->motion.height >> 8;
            func_0809836C(state->actor, 7, state->direction, state->animation);
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 3;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_08141520(0x91);
            state->phase = 3;
        }
        break;
    }
    case 3: {
        Motion *motion;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->y = state->motion.height >> 8;
        func_080A9E6C(state, 4);
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
        state->count++;
        state->effect_x = target->x - state->step_x * 16;
        /* The ROM adds 8 to the remainder (0x080AF056) before it adds
         * target->y (0x080AF058-0x080AF05A), with no extension between;
         * src/080AB674.c spells the same step this way, and src/080AB358.c
         * with an explicit func_08142950 call. */
        state->effect_y = (s16)((s16)func_08002804() % 9 + 8) + target->y;
        state->effect_z = target->z - state->step_z * 16;
        state->effect_flag = 1;
        state->effect_flag2 = 0;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        func_08141520(0x8B);
        state->flags &= ~2;
        state->motion.destination =
            func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
        state->motion.height = target->y << 8;
        state->motion.velocity = -0x800;
        position.y = func_08099C1C(target, target->x >> 5, target->z >> 5) << 4;
        position.x = target->x;
        position.z = target->z;
        func_080A83A4(&position, 8, 1, -0x78, -0x56);
        state->phase = 4;
        break;
    }
    case 4: {
        Motion *motion;
        s32 moving;

        func_080A83DC();
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
        if (func_08099C64(state->actor)) {
            state->actor->flags |= 1;
            state->flags &= ~2;
        }
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
            state->phase = 5;
        }
        break;
    }
    case 5:
        if (func_08099C64(state->actor)) {
            state->actor->flags |= 1;
            state->flags &= ~2;
        }
        if (func_080A83DC() == 0) {
            state->actor->flags |= 1;
            state->flags = 0;
            return 0;
        }
        break;
    }
    return 1;
}
