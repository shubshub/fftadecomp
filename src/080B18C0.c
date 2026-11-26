#include "ffta.h"

/* Complete [0x080B18C0, 0x080B264C): 3468 bytes, including the nine-entry
 * jump table at 0x080B1B4C and the middle literals. */

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

/* The state stack, as src/08092784.c and src/080BBE00.c declare it. */
typedef struct {
    u16 current, depth, stack[34];
} Phase;

typedef struct {
    Actor *actor;
    Motion motion;
    Motion slide;
    u8 unknown_1C[6];
    s16 timer;
    u8 unknown_24[0x12];
    u16 animation;
    u8 unknown_38[6];
    s8 direction;
    s8 count;
    u8 flags;
    u8 unknown_41[3];
    Trail trail;
    u16 unknown_94[3];
    u8 unknown_9A[0x5A];
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
    Phase phase;
} State;

/* The field order of src/0809DE00.c's QueryRegion, as src/080AC05C.c declares it. */
typedef struct {
    s32 top;
    s32 bottom;
    s32 left;
    s32 right;
} Rect;

/* Heading turn for each direction, added to the 16-step heading. */
extern const s8 data_08394589[4];

extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_080A9B00(Trail *trail);
extern void func_08007AD0(Homing *homing);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_0809A09C(Actor *actor);
extern void func_0809A298(Actor *actor, u16 value, s8 adjustment);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern void func_080E2C00(void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern void func_08141520(u16 sound);
extern s32 func_08099C1C(Actor *actor, s8 x, s8 z);
extern u16 func_08021C8C(const void *object);
extern u32 func_08021E60(const void *object);
extern const void *func_08021DA8(const void *object, u8 *flip_x, u8 *flip_y);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);

/* The state stack's push and pop, as src/080BBE00.c writes them.  The ROM
 * addresses depth from the phase record's base (ldrh [r2, #2] after
 * r2 = state + 0x13C, at 0x080B2488 and 0x080B24D6). */
static inline void push_state(Phase *phase)
{
    phase->stack[phase->depth++] = phase->current;
}

static inline void pop_state(Phase *phase)
{
    phase->current = phase->stack[--phase->depth];
}

/* Clears count halfwords.  The ROM keeps the loop counter (movs r1, #2 at
 * 0x080B229C, subs r1, #1 / cmp r1, #0 at 0x080B22A6) beside the
 * descending pointer; a loop over state->unknown_94[i] written out in the
 * case compares the pointer against its bound instead (src/080B0E78.c). */
static inline void clear_halfwords(u16 *words, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++)
        words[i] = 0;
}

/* Moves the actor along its step by distance.  Case 1 steps by 3 with the
 * distance in a register (movs r3, #3 at 0x080B1DC2, muls at 0x080B1DD4 and
 * 0x080B1DEA); case 8 steps by 4, which agbcc turns into lsls #2. */
static inline void step_actor(State *state, s32 distance)
{
    if (state->step_x != 0)
        state->actor->x += state->step_x * distance;
    if (state->step_z != 0)
        state->actor->z += state->step_z * distance;
}

u32 func_080B18C0(State *state, Actor *target, void *task, void *effect)
{
    s8 left;
    s8 right;
    u8 flip_x;
    u8 flip_y;

    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 4;
        state->transition.second = 2;
        state->transition.third = 3;
        state->transition.level = 8;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    if (state->flags & 8) {
        u16 dx;
        u16 dz;

        dx = abs(state->actor->x - target->x);
        /* dz is never read.  The ROM keeps its loads and subtraction
         * (0x080B194E-0x080B1958, again at 0x080B1CDA-0x080B1CE4): the
         * abs() whose test and negation were removed as unused, as in
         * src/080B0510.c. */
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
        state->heading = (state->heading + data_08394589[state->direction]) & 15;
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
            if (state->phase.current == 1) {
                func_08141520(0x7B);
            } else {
                func_08141520(0x11A);
                state->motion.velocity = 0x300;
            }
            state->flags |= 0x10;
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

    switch (state->phase.current) {
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
        state->motion.velocity = 0xB00;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        func_0809A570(state->actor, 0, 0x1000);
        state->phase.current = 1;
        break;
    case 1: {
        Motion *motion;
        s32 moving;
        s32 distance;
        u16 dx;
        u16 dz;

        if (func_08099C34(state->actor) == 0) {
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
            func_08141520(0x91);
            state->flags |= 0xC;
        }
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
        step_actor(state, 3);
        if (!moving && (state->flags & 0xC) == 0) {
            func_0809836C(state->actor, 7, state->direction, 0);
            state->count = 2;
            state->step_x *= -1;
            state->step_z *= -1;
            state->destination_x = (((target->x >> 5) + state->step_x * 2) << 5) + 16;
            state->destination_z = (((target->z >> 5) + state->step_z * 2) << 5) + 16;
            state->slide.destination = 0;
            if (state->step_x != 0)
                distance = state->actor->x - state->destination_x;
            else
                distance = state->actor->z - state->destination_z;
            /* The ROM negates and shifts distance in its own register
             * (0x080B1E9A-0x080B1EA2), as 0x080AC1E6-0x080AC1F0 does. */
            if (distance < 0)
                distance = -distance;
            distance <<= 8;
            state->slide.height = distance;
            state->slide.velocity = -0x200;
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 3;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->phase.current = 3;
        }
        break;
    }
    /* Cases 3 and 4 come before case 2 in the ROM (0x080B1F00, 0x080B210C,
     * then 0x080B2220). */
    case 3: {
        Motion *motion;
        Rect actor_rect;
        Rect target_rect;
        s8 direction;

        motion = &state->slide;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->x = state->destination_x - (state->slide.height >> 8) * state->step_x;
        state->actor->z = state->destination_z - (state->slide.height >> 8) * state->step_z;
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
            func_08141520(0x7B);
            state->effect_x = target->x - state->step_x * 16;
            state->effect_y = (s16)((s16)func_08002804() % 9 + 8) + target->y;
            state->effect_z = target->z - state->step_z * 16;
            state->effect_flag = 1;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->flags |= 0x10;
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            func_080A8390(state->actor->direction, target->direction, &left, &right);
            if (left != 0)
                func_0809A570(target, 0, 0x200);
            if (right != 0)
                func_0809A570(target, 0, 0x400);
            state->slide.velocity *= -1;
            state->slide.height = 0;
            state->destination_x = state->actor->x;
            state->destination_z = state->actor->z;
            state->count = 1;
            /* One sign-extending load (ldrsb at 0x080B20DA) and one store
             * (0x080B20EE): direction = state->direction + 2 loads with
             * ldrb, and adding to the member stores twice. */
            direction = state->direction;
            direction += 2;
            if (direction > 3)
                direction -= 4;
            state->direction = direction;
            func_0809A298(state->actor, 0xC, state->direction);
            state->phase.current = 4;
        }
        break;
    }
    case 4: {
        Motion *motion;

        if (++state->timer > 6) {
            state->timer = 0;
            state->flags |= 0x10;
            state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
            state->effect_y = target->y + (s16)func_08002804() % 41;
            state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
            state->effect_flag = 1;
            state->effect_flag2 = 1;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_08141520(0x7B);
        }
        motion = &state->slide;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        if (state->slide.velocity >= 0) {
            state->actor->x = state->destination_x + (state->slide.height >> 8) * state->step_x;
            state->actor->z = state->destination_z + (state->slide.height >> 8) * state->step_z;
        } else {
            state->timer = 0;
            state->phase.current = 2;
        }
        break;
    }
    case 2: {
        s32 i;

        if (++state->timer == 0x18) {
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 7;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_08141520(0x124);
        }
        if (state->timer > 0x2F) {
            func_0809A298(state->actor, 0x34, state->direction);
            state->timer = 0;
            clear_halfwords(state->unknown_94, 3);
            func_0809A570(state->actor, 0, 0x2000);
            state->phase.current = 5;
        }
        break;
    }
    case 5: {
        Motion *motion;
        s32 dx;

        if (state->timer != 0) {
            motion = &state->motion;
            motion->height += motion->velocity;
            motion->velocity -= 0x99;
            if (motion->destination >= motion->height && motion->velocity <= 0)
                motion->height = motion->destination;
            target->y = state->motion.height >> 8;
        }
        if (func_08099C34(state->actor) != 0)
            break;
        /* Full width here: the ROM keeps dx in sb with no lsls/lsrs #16
         * after the negation (0x080B2310-0x080B2318). */
        dx = abs(state->actor->x - target->x);
        state->trail.axis |= 1;
        state->effect_x = state->actor->x;
        state->effect_y = state->actor->y;
        state->effect_z = state->actor->z;
        state->effect_flag = 2;
        state->effect_flag2 = 3;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->trail.homing.target_y = target->y << 8;
        state->trail.homing.current_y = state->actor->y << 8;
        state->trail.y = state->actor->y;
        if (dx != 0) {
            state->trail.homing.target_x = target->x << 8;
            state->trail.homing.current_x = state->actor->x << 8;
            state->trail.axis |= 2;
        } else {
            state->trail.homing.target_x = target->z << 8;
            state->trail.homing.current_x = state->actor->z << 8;
            state->trail.axis &= ~2;
        }
        if (state->trail.axis & 2)
            state->trail.x = state->trail.homing.current_x >> 8;
        else
            state->trail.z = state->trail.homing.current_x >> 8;
        state->trail.homing.speed = 1;
        state->trail.homing.turn_percent = 100;
        func_08007AD0(&state->trail.homing);
        state->trail.homing.turn_percent = 5;
        state->trail.homing.speed = 0xE00;
        state->heading = 0;
        state->flags |= 0xC;
        if (state->timer == 0) {
            state->motion.destination =
                func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
            state->motion.height = target->y << 8;
            state->motion.velocity = 0xA00;
        }
        if (++state->timer > 1) {
            func_0809A570(state->actor, 0, 0x100);
            state->flags |= 2;
            state->phase.current = 7;
        } else {
            push_state(&state->phase);
            state->phase.current = 6;
        }
        break;
    }
    case 6:
        if (state->flags & 0xC)
            break;
        func_0809836C(state->actor, 7, state->direction, 0);
        func_0809A570(state->actor, 0, 0x2000);
        pop_state(&state->phase);
        break;
    case 7: {
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
        if (moving)
            break;
        func_08141520(0x89);
        func_0809836C(target, 5, target->direction, 0);
        state->effect_x = target->x;
        state->effect_y = target->y;
        state->effect_z = target->z;
        state->effect_flag = 2;
        state->effect_flag2 = 0;
        func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                      state->effect_flag, state->effect_flag2);
        state->actor->attachment = state->attachment;
        func_0809A09C(state->actor);
        state->motion.destination = (state->actor->y - 0x30) << 8;
        state->motion.height = state->actor->y << 8;
        state->motion.velocity = 0x800;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 3, state->direction, 0);
        state->phase.current = 8;
        break;
    }
    case 8: {
        Motion *motion;
        s32 moving;

        step_actor(state, 4);
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
        if (!moving) {
            state->actor->flags |= 1;
            state->flags = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}
