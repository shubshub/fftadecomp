#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    s8 x;
    s8 y;
    s8 height;
} UnitPosition;

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

struct ActionState {
    void *source;
    u8 unknown_04[4];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

extern u32 func_08002804(void);
extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CDE14(void *object, u8 enabled);
extern void func_080CDE38(void *object, u8 enabled);
extern void func_080CDE5C(Object *object, u8 enabled);
extern void func_080CE02C(void *object, u8 enabled);
extern void func_080CE0B8(void *object, u8 enabled);
extern void func_080CE0DC(void *object, u8 enabled);
extern void func_080CE100(void *object, u8 enabled);
extern u32 func_0812F008(UnitPosition *first, UnitPosition *second, u32 options);
extern void func_08131DD4(u8 *buffer, s32 index);

static inline s16 random_roll(void)
{
    return (s16)func_08002804() % 1001;
}

/* Effect descriptor table 083A87B0, slot 43. Each status has its own roll. */
void func_081326AC(struct ActionState *state)
{
    u8 count;

    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
        return;
    }

    count = 0;
    {
        s32 threshold = func_0812F008(state->source, state->target, 0x33) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 22);
            if (!(state->flags & 0x10))
                func_080CE02C(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x23) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 10);
            if (!(state->flags & 0x10))
                func_080CDE5C(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x29) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 28);
            if (!(state->flags & 0x10))
                func_080CE100(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x38) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 27);
            if (!(state->flags & 0x10))
                func_080CE0DC(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x0C) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 8);
            if (!(state->flags & 0x10))
                func_080CDE14(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x3D) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 9);
            if (!(state->flags & 0x10))
                func_080CDE38(state->target, 1);
        }
    }

    {
        s32 threshold = func_0812F008(state->source, state->target, 0x2D) * 10;
        s16 roll = random_roll();

        if (threshold >= roll) {
            count++;
            func_08131DD4((u8 *)state, 26);
            if (!(state->flags & 0x10))
                func_080CE0B8(state->target, 1);
        }
    }
    if (count == 0)
        state->flags |= 0x100;
}
