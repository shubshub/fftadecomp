#include "effect_registry.h"

struct Group080DD4A4;
struct Child080DD4A4;
struct PositionSourceLink;
struct Object;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    struct Group080DD4A4 *group;
} EffectCommand;

typedef struct {
    u16 position;
    u8 palette;
    u8 unknown_03;
    void *transition;
    void *pieces;
    s16 x, y;
    u8 unknown_10[4];
    void *entity;
    void *child;
    struct Group080DD4A4 *group;
} EffectState;

typedef struct {
    u16 first;
    u16 second;
    u16 third;
    u8 level;
} TransitionParameters080E2848;

typedef struct {
    s16 x, y;
} Offset;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern InputState data_03000000;
extern struct Child080DD4A4 *func_080DD4A4(struct Group080DD4A4 *, u8);
extern struct PositionSourceLink *func_080DD748(struct PositionSourceLink *, s16 *, s16 *, s16 *);
extern int func_080E28A8(const void *);
extern u8 func_080E2BDC(void *);
extern void *func_080DBA5C(void *);
extern void func_080E2848(void *, const TransitionParameters080E2848 *);
extern void func_080DBA50(void *);
extern void func_080DE10C(struct Object *, u16);
extern void func_080E29C4(void *, s16, s16, u8, u8);
extern u32 func_080D3888(u32);

/* Complete Thumb function at 08120BF4..08120DEE. */
u32 func_08120BF4(void *task, EffectCommand *command, EffectState *state)
{
    switch (command->phase) {
    case 0:
        state->group = command->group;
        state->palette = 0;
        break;
    case 2:
        break;
    case 0x100:
        state->entity = func_080DD748((struct PositionSourceLink *)func_080DD4A4(state->group, 0),
                                      &state->x, &state->y, 0);
        state->transition = func_080D3508(0x15A, state->group, 0);
        state->pieces = func_080D3508(0x15B, state->group, 0);
        command->phase++;
        break;
    case 0x101:
        if ((u8)func_080E28A8(state->transition) && func_080E2BDC(state->pieces))
            command->phase++;
        break;
    case 0x102: {
        TransitionParameters080E2848 transition = {2, 2, 2, 10};
        Offset offsets[8] = {
            {0, 0}, {-10, -8}, {8, 10}, {10, -8},
            {-8, 10}, {0, -10}, {-12, 4}, {-12, -4}
        };

        if (data_03000000.pressed & 0x100) {
            if (++state->palette > 5)
                state->palette = 0;
        }
        state->child = func_080DBA5C(state->child);
        if (data_03000000.pressed & 3) {
            u16 x, y;
            u8 group;
            func_080E2848(state->transition, &transition);
            if (state->child) {
                func_080DBA50(state->child);
                state->child = 0;
            }
            func_080DE10C(state->entity, 8);
            group = 0;
            if (data_03000000.held & 0x80) {
                group = 2;
                if (data_03000000.pressed & 2)
                    group = 3;
                x = state->x;
                y = state->y;
            } else if (data_03000000.held & 0x40) {
                group = 4;
                if (data_03000000.pressed & 2)
                    group = 7;
                x = state->x;
                y = state->y;
            } else if (data_03000000.held & 0x20) {
                group = 5;
                if (data_03000000.pressed & 2)
                    group = 6;
                x = state->x;
                y = state->y;
            } else {
                const Offset *offset;
                if (data_03000000.pressed & 2)
                    group = 1;
                offset = &offsets[state->position];
                x = offset->x;
                x += state->x;
                y = offset->y - 12;
                y += state->y;
            }
            func_080E29C4(state->pieces, x, y, group, state->palette);
            state->position = (state->position + 1) & 7;
        }
        if (data_03000000.pressed & 8)
            command->phase++;
        break;
    }
    case 0x103:
        state->child = func_080DBA5C(state->child);
        if (!state->child) {
            state->transition = (void *)func_080D3888((u32)state->transition);
            state->pieces = (void *)func_080D3888((u32)state->pieces);
            if (!state->transition && !state->pieces)
                command->phase = 2;
        }
        break;
    }
    return 0;
}
