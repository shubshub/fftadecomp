#include "ffta.h"

/* Complete [0x080AC05C, 0x080ACC22): 3014 bytes, including the 9-word
 * phase jump table at 0x080AC0DC and the middle literals. */

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
    s16 x;
    s16 y;
    s16 z;
    u16 unknown_06;
} Position;

/* The field order of src/0809DE00.c's QueryRegion. */
typedef struct {
    s32 top;
    s32 bottom;
    s32 left;
    s32 right;
} Rect;

typedef struct {
    Actor *actor;
    Motion motion;
    /* Cases 0 and 1 keep the hit flag in target_motion.destination:
     * 0 until the hit, -1 after it (0x080AC20E, 0x080AC49C). */
    Motion target_motion;
    u8 unknown_1C[6];
    s16 timer;
    u8 unknown_24[0x12];
    u16 commands[2];
    u16 unknown_3A;
    u8 unknown_3C;
    u8 command_count;
    s8 direction;
    s8 count;
    u8 flags;
    u8 unknown_41;
    u16 unknown_42;
    u8 unknown_44[0xB0];
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
    /* Cases 3 and 4 use destination_x as a flag (0x080AC7FC, 0x080AC946). */
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
} State;

/* Direction offsets for the nine hits: 0, -2, 1, -1, 0, -2, 1, -1, 0.
 * Nine bytes: the next table, data_08394579, has its own literal word
 * (0x080AD55C). */
extern const s8 data_08394570[9];

extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u32 func_080A83A4(const Position *source, u32 value_08, u32 value_0E,
                         u32 value_0A, u32 value_0C);
extern void func_080A7EC4(u16 command);
extern u32 func_080A83DC(void);
extern u32 func_08099C64(const Actor *actor);
extern void func_0809A09C(Actor *actor);
extern void func_0809A298(Actor *actor, u16 value, s8 adjustment);

u32 func_080AC05C(State *state, Actor *target, void *task, void *effect)
{
    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 6;
        state->transition.level = 8;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    switch (state->phase) {
    case 0: {
        s32 distance;

        state->unknown_42 = target->y;
        if (state->command_count < 2)
            state->commands[1] = state->commands[0];
        state->flags |= 2;
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x * 5) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z * 5) << 5) + 16;
        state->actor->y = target->y;
        state->destination_x = (((target->x >> 5) + state->step_x * 2) << 5) + 16;
        state->destination_z = (((target->z >> 5) + state->step_z * 2) << 5) + 16;
        state->motion.destination = 0;
        if (state->step_x != 0)
            distance = state->actor->x - state->destination_x;
        else
            distance = state->actor->z - state->destination_z;
        if (distance < 0)
            distance = -distance;
        /* The ROM shifts distance in its own register (0x080AC1F0). */
        distance <<= 8;
        state->motion.height = distance;
        state->motion.velocity = 0;
        func_0809836C(state->actor, 7, state->direction, state->commands[0]);
        state->phase = 1;
        state->target_motion.destination = 0;
        break;
    }
    case 1: {
        Motion *motion;
        Rect actor_rect;
        Rect target_rect;
        s8 left;
        s8 right;

        if (state->target_motion.destination != 0) {
            if (state->count != 0) {
                motion = &state->motion;
                motion->height += motion->velocity;
                motion->velocity -= 0x99;
                if (motion->destination >= motion->height && motion->velocity <= 0)
                    motion->height = motion->destination;
            }
            state->count ^= 1;
            state->actor->flags ^= 1;
            if (state->motion.velocity >= 0) {
                state->actor->x = state->destination_x + (state->motion.height >> 8) * state->step_x;
                state->actor->z = state->destination_z + (state->motion.height >> 8) * state->step_z;
            }
        } else {
            motion = &state->motion;
            motion->height += motion->velocity;
            motion->velocity -= 0x99;
            if (motion->destination >= motion->height && motion->velocity <= 0)
                motion->height = motion->destination;
            state->actor->x = state->destination_x - (state->motion.height >> 8) * state->step_x;
            state->actor->z = state->destination_z - (state->motion.height >> 8) * state->step_z;
        }
        if (state->target_motion.destination == 0) {
            actor_rect.left = state->actor->x - 16;
            actor_rect.top = state->actor->z - 16;
            actor_rect.right = state->actor->x + 16;
            actor_rect.bottom = state->actor->z + 16;
            target_rect.left = target->x - 16;
            target_rect.top = target->z - 16;
            target_rect.right = target->x + 16;
            target_rect.bottom = target->z + 16;
            if (actor_rect.left < target_rect.right && actor_rect.right > target_rect.left
                && actor_rect.top < target_rect.bottom && actor_rect.bottom > target_rect.top) {
                func_080A7EC4(state->commands[0]);
                state->flags |= 0x10;
                func_0809836C(target, 5, target->direction, 0);
                func_0809A570(target, 0, 0x8000);
                func_080A8390(state->actor->direction, target->direction, &left, &right);
                state->effect_x = target->x - state->step_x * 16;
                /* The ROM adds 8 to the remainder (0x080AC3E0) before it adds
                 * target->y (0x080AC3E2-0x080AC3E6), as src/080AB358.c and
                 * src/080AB674.c spell the same step. */
                state->effect_y = (s16)((s16)func_08002804() % 9 + 8) + target->y;
                state->effect_z = target->z - state->step_z * 16;
                state->effect_flag = 1;
                state->effect_flag2 = 0;
                func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                              state->effect_flag, state->effect_flag2);
                func_0809A570(target, 0, 0x100);
                func_0809A570(state->actor, 0, 0x100);
                if (left != 0)
                    func_0809A570(target, 0, 0x200);
                if (right != 0)
                    func_0809A570(target, 0, 0x400);
                state->motion.velocity = -state->motion.velocity;
                state->motion.height = 0;
                state->destination_x = state->actor->x;
                state->destination_z = state->actor->z;
                state->target_motion.destination = -1;
                state->count = 0;
                state->timer = 0x20;
                state->phase = 2;
            }
        }
        if (state->target_motion.destination != 0 && state->motion.velocity < 0
            && func_08099C64(state->actor)) {
            state->phase = 5;
            state->timer = 0;
        }
        break;
    }
    case 2: {
        s32 direction;

        if (state->timer > 0) {
            state->timer--;
            break;
        }
        direction = state->direction;
        direction += data_08394570[state->count];
        if (direction < 0)
            direction += 4;
        if (direction > 3)
            direction -= 4;
        state->flags |= 0x10;
        func_0809D66C(direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->count = 0;
        func_0809836C(state->actor, 7, direction, state->commands[!(state->count & 1)]);
        state->motion.destination = func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
        state->motion.height = target->y << 8;
        state->motion.velocity = 0x600;
        func_0809A570(state->actor, 0, 0x2000);
        state->flags &= ~2;
        state->phase = 3;
        break;
    }
    case 3: {
        Motion *motion;
        s8 left;
        s8 right;
        s32 direction;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
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
        state->motion.velocity = 0x280;
        state->effect_x = target->x - state->step_x * 16;
        state->effect_y = (s16)((s16)func_08002804() % 9 + 8) + target->y;
        state->effect_z = target->z - state->step_z * 16;
        state->effect_flag = 0;
        state->effect_flag2 = 1;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        if (state->count >= sizeof(data_08394570)) {
            state->count = 0;
            state->actor->x = (((target->x >> 5) + state->step_x) << 5) + 16;
            state->actor->z = (((target->z >> 5) + state->step_z) << 5) + 16;
            state->motion.velocity = 0xA00;
            state->motion.height = state->actor->y << 8;
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 2;
            state->effect_flag2 = 3;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_0809A09C(state->actor);
            func_0809A298(state->actor, 12, state->actor->direction);
            state->flags |= 2;
            state->destination_x = 0;
            state->phase = 4;
        } else {
            direction = state->direction;
            direction += data_08394570[state->count];
            if (direction < 0)
                direction += 4;
            if (direction > 3)
                direction -= 4;
            func_080A7EC4(state->commands[0]);
            state->flags |= 0x10;
            func_0809D66C(direction, &state->step_x, &state->step_z);
            state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
            state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
            state->destination_x = (((target->x >> 5) - state->step_x) << 5) + 16;
            state->destination_z = (((target->z >> 5) - state->step_z) << 5) + 16;
            func_0809836C(state->actor, 7, direction, state->commands[!(state->count & 1)]);
            state->actor->y = target->y;
            func_0809A570(state->actor, 0, 0x2000);
        }
        break;
    }
    case 4: {
        Motion *motion;
        s8 direction;

        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        target->y = state->motion.height >> 8;
        if (target->y < state->actor->y + 0x40 && state->motion.velocity < 0
            && state->destination_x == 0) {
            direction = state->actor->direction - 2;
            if (direction < 0)
                direction += 4;
            state->destination_x = 1;
            func_0809836C(state->actor, 7, direction, state->commands[0]);
            func_0809A570(state->actor, 0, 0x2000);
        }
        if (func_08099C34(state->actor) != 0)
            break;
        func_0809A570(state->actor, 0x2000, 0);
        state->destination_x = 0;
        state->flags |= 0x10;
        func_0809836C(target, 5, target->direction, 0);
        func_0809A570(target, 0, 0x8000);
        state->effect_x = target->x;
        state->effect_y = target->y;
        state->effect_z = target->z;
        state->effect_flag = state->count + 5;
        state->effect_flag2 = 1;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->effect_x = state->actor->x;
        state->effect_y = state->actor->y;
        state->effect_z = state->actor->z;
        state->effect_flag = 3;
        state->effect_flag2 = 3;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->count++;
        state->motion.velocity = 0x600;
        state->step_x *= -1;
        state->step_z *= -1;
        state->actor->x = (((target->x >> 5) + state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) + state->step_z) << 5) + 16;
        state->motion.height = state->actor->y << 8;
        func_08141520(0x7B);
        if (state->count > 1) {
            state->phase = 7;
            state->timer = 0x20;
            func_0809A570(target, 0, 0x100);
        }
        break;
    }
    case 7: {
        Position position;

        if (state->timer >= 0) {
            state->timer--;
            break;
        }
        state->flags &= ~2;
        state->actor->flags |= 1;
        position.y = func_08099C1C(target, target->x >> 5, target->z >> 5) << 4;
        position.x = target->x;
        position.z = target->z;
        func_080A83A4(&position, 8, 1, -0x78, -0x56);
        state->target_motion.destination =
            func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
        state->target_motion.height = target->y << 8;
        state->target_motion.velocity = 0;
        state->phase = 8;
        break;
    }
    case 8: {
        Motion *motion;
        u32 pending;
        s32 moving;

        pending = func_080A83DC();
        motion = &state->target_motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0) {
            motion->height = motion->destination;
            moving = 0;
        } else {
            moving = 1;
        }
        target->y = state->target_motion.height >> 8;
        if (!pending && !moving) {
            /* The ROM toggles bit 0 and then sets it, with one load and one
             * store (eors/orrs at 0x080ACBA6-0x080ACBA8). */
            state->actor->flags ^= 1;
            state->actor->flags |= 1;
            state->flags = 0;
            func_0809836C(target, 5, target->direction, 0);
            state->effect_x = target->x;
            state->effect_y = target->y;
            state->effect_z = target->z;
            state->effect_flag = 2;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_0809A09C(state->actor);
            func_08141520(0x89);
            return 0;
        }
        break;
    }
    }
    return 1;
}
