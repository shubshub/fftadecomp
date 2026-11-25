#include "ffta.h"

/* Complete [0x080B0E78, 0x080B18C0): 2632 bytes, including the ten-entry
 * jump table at 0x080B1060 and the middle literals. */

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

/* The record func_080A9B00 updates (src/080A9B00.c). */
typedef struct {
    const void *graphics;
    u8 unknown_04[0x28];
    u16 flags;
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_34[4];
    u16 angle;
    u16 value;
    u16 parameter;
} PositionRecord;

typedef struct {
    Actor *actor;
    Motion motion;
    Motion record_motion;
    u8 unknown_1C[6];
    s16 timer;
    u8 unknown_24[0xC];
    u16 unknown_30[3];
    u16 commands[2];
    u16 unknown_3A;
    u8 command;
    u8 command_count;
    s8 direction;
    s8 count;
    u8 flags;
    u8 unknown_41[3];
    PositionRecord record;
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

/* The spin step for each direction: -1, 1, 1, -1 (literal word 0x080B1058). */
extern const s8 data_08394585[4];

extern s32 abs(s32 value);
extern u8 func_080D3878(const void *task);
extern void func_080E2848(void *task, const Transition *parameters);
extern void func_080A9B00(PositionRecord *record);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern u8 func_080A9E6C(State *state, s32 distance);
extern s32 func_08099C34(Actor *actor);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_0809A09C(Actor *actor);
extern void func_0809A298(Actor *actor, u16 value, s8 adjustment);
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
extern const void *func_08021DA8(const void *object, u8 *flip_x, u8 *flip_y);
extern u16 func_08021C8C(const void *object);
extern u32 func_08021E60(const void *object);
extern void func_08021DE4(u32 *flags, u16 clear, u16 set);

u32 func_080B0E78(State *state, Actor *target, void *task, void *effect)
{
    if ((state->flags & 0x10) && func_080D3878(task)) {
        state->transition.first = 2;
        state->transition.second = 2;
        state->transition.third = 2;
        state->transition.level = 6;
        func_080E2848(task, &state->transition);
        state->flags &= ~0x10;
    }

    if (state->flags & 8) {
        state->record.angle = state->spin << 12;
        state->spin = (state->spin + data_08394585[state->direction]) & 0xF;
        func_080A9B00(&state->record);
        if (abs(target->x - state->record.x) + abs(target->z - state->record.z)
                + abs(target->y - state->record.y) < 32
            && --state->timer <= 0) {
            state->count++;
            state->timer = 8;
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            state->flags |= 0x10;
            func_080A7EC4(state->commands[state->command]);
            state->effect_x = target->x + (s16)func_08002804() % 41 - 20;
            state->effect_y = target->y + (s16)func_08002804() % 41;
            state->effect_z = target->z + (s16)func_08002804() % 41 - 20;
            state->effect_flag = 1;
            state->effect_flag2 = 1;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            if (state->count == 4)
                state->record_motion.velocity = 0xE00;
        }
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
        state->motion.height = (target->y - 0x30) << 8;
        state->motion.velocity = 0x900;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->commands[0]);
        state->phase = 1;
        break;
    case 1: {
        Motion *motion;
        s8 left;
        s8 right;
        u8 flip_x;
        u8 flip_y;

        if (func_08099C34(state->actor) == 0) {
            func_080A7EC4(state->commands[state->command]);
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            func_080A8390(state->actor->direction, target->direction, &left, &right);
            if (left != 0)
                func_0809A570(target, 0, 0x200);
            if (right != 0)
                func_0809A570(target, 0, 0x400);
            state->effect_x = target->x - state->step_x * 16;
            /* src/080AE7D8.c's spelling of this step: the ROM adds 8 to the
             * remainder (0x080B11FA) before it adds target->y (0x080B11FC). */
            state->effect_y = (s16)((s16)func_08002804() % 9 + 8) + target->y;
            state->effect_z = target->z - state->step_z * 16;
            state->effect_flag = 0;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            state->saved_flags = state->actor->additional_flags;
            state->actor->additional_flags = 0;
            state->record.value = func_08021C8C(state->saved_flags);
            state->record.parameter = func_08021E60(state->saved_flags);
            state->record.graphics = func_08021DA8(state->saved_flags, &flip_x, &flip_y);
            state->record.angle = 0;
            state->record.x = state->actor->x;
            state->record.y = state->actor->y;
            state->record.z = state->actor->z;
            func_08021DE4(state->saved_flags, 0x40, 0x100);
            func_0809A298(state->actor, 0x3C, state->direction);
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
        if (func_08099C34(state->actor) >= 0) {
            state->flags |= 0xC;
            state->record.flags |= 1;
            func_0809836C(target, 5, target->direction, 0);
            func_0809A570(target, 0, 0x8000);
            func_0809A570(state->actor, 0, 0x100);
            func_080A7EC4(state->commands[state->command]);
            state->flags |= 0x10;
            state->record_motion.destination = state->record.y << 8;
            state->record_motion.height = state->record.y << 8;
            state->record_motion.velocity = 0xF00;
            state->phase = 3;
        }
        break;
    case 3:
        if (state->record_motion.velocity > 0) {
            Motion *motion;

            motion = &state->record_motion;
            motion->height += motion->velocity;
            motion->velocity -= 0x99;
            if (motion->destination >= motion->height && motion->velocity <= 0)
                motion->height = motion->destination;
            state->record.y = state->record_motion.height >> 8;
        } else {
            s32 i;

            func_08141520(0x91);
            func_0809A298(state->actor, 0x38, state->direction);
            func_0809A570(state->actor, 0, 0x100);
            /* src/080ACC24.c's text: the ROM sign-extends each step before
             * negating it (ldrsb at 0x080B13DE and 0x080B13EA). */
            state->step_x *= -1;
            state->step_z *= -1;
            state->motion.destination = (state->actor->y + 0x30) << 8;
            state->flags |= 2;
            state->flags &= ~0xC;
            /* The ROM clears 0x34 down to 0x30 against a pointer bound
             * (0x080B1414-0x080B141A): agbcc reverses this counting loop,
             * as it does src/0808F8E8.c's. */
            for (i = 0; i < 3; i++)
                state->unknown_30[i] = 0;
            state->motion.height = state->actor->y << 8;
            state->motion.velocity = 0x900;
            state->phase = 4;
        }
        break;
    case 4: {
        Motion *motion;
        s32 moving;

        if (state->step_x != 0)
            state->actor->x += state->step_x * 4;
        if (state->step_z != 0)
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
        if (!moving) {
            /* As in case 3: ldrsb at 0x080B14B0 and 0x080B14BC. */
            state->step_x *= -1;
            state->step_z *= -1;
            state->motion.destination = target->y << 8;
            state->motion.height = state->actor->y << 8;
            state->motion.velocity = 0x1000;
            state->destination_x = (((target->x >> 5) + state->step_x) << 5) + 16;
            state->destination_z = (((target->z >> 5) + state->step_z) << 5) + 16;
            func_08141520(0x91);
            state->effect_x = state->actor->x;
            state->effect_y = state->actor->y;
            state->effect_z = state->actor->z;
            state->effect_flag = 3;
            state->effect_flag2 = 0;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_0809836C(state->actor, 3, state->direction, 0);
            state->phase = 5;
        }
        break;
    }
    case 5: {
        Motion *motion;

        func_080A9E6C(state, 4);
        motion = &state->motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->actor->y = state->motion.height >> 8;
        if (state->motion.velocity < 0) {
            state->record.x = target->x;
            state->record.z = target->z;
            state->flags |= 0xC;
            state->phase = 6;
        }
        break;
    }
    case 6: {
        Motion *motion;

        motion = &state->record_motion;
        motion->height += motion->velocity;
        motion->velocity -= 0x99;
        if (motion->destination >= motion->height && motion->velocity <= 0)
            motion->height = motion->destination;
        state->record.y = state->record_motion.height >> 8;
        if (state->record_motion.velocity <= 0 && state->count > 3) {
            state->flags &= ~0xC;
            state->actor->additional_flags = state->saved_flags;
            func_0809A09C(state->actor);
            state->actor->direction += 2;
            if (state->actor->direction > 3)
                state->actor->direction -= 4;
            state->flags |= 2;
            func_0809836C(state->actor, 7, state->actor->direction, state->commands[0]);
            state->timer = 0;
            state->count = 0;
            state->phase = 7;
        }
        break;
    }
    case 7: {
        Motion *motion;
        s32 moving;
        s8 left;
        s8 right;
        Position position;

        func_080A9E6C(state, 4);
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
            state->flags &= ~2;
            state->effect_x = target->x;
            state->effect_y = target->y + 8;
            state->effect_z = target->z;
            state->effect_flag = 4;
            state->effect_flag2 = 1;
            func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                          state->effect_flag, state->effect_flag2);
            func_08141520(0xFD);
            func_0809836C(target, 5, target->direction, 0);
            func_080A8390(state->actor->direction, target->direction, &left, &right);
            if (left != 0)
                func_0809A570(target, 0, 0x200);
            if (right != 0)
                func_0809A570(target, 0, 0x400);
            state->flags |= 0x10;
            state->motion.destination =
                func_08099C1C(target, target->x >> 5, target->z >> 5) << 12;
            state->motion.height = target->y << 8;
            state->motion.velocity = -0x800;
            position.y = func_08099C1C(target, target->x >> 5, target->z >> 5) << 4;
            position.x = target->x;
            position.z = target->z;
            func_080A83A4(&position, 8, 1, -0x78, -0x56);
            state->phase = 8;
        }
        break;
    }
    case 8:
    case 9: {
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
        if (!moving && state->phase == 8) {
            state->phase = 9;
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
        pending = func_080A83DC();
        if (func_08099C64(state->actor) == 1 && !pending && state->phase == 9) {
            func_0809A09C(state->actor);
            state->actor->flags |= 1;
            state->flags &= ~2;
            return 0;
        }
        break;
    }
    }
    return 1;
}
