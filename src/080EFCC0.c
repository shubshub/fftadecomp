#include "ffta.h"

/* 0x080EFCC0 .. 0x080EFD4E: 142 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 flags;
} Command080EFCC0;

typedef struct {
    u8 flags;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *actor;
    void *effect;
} State080EFCC0;

extern const u8 data_08399C1C[];
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080DCFE4(void *, const void *, int, int, int, void *, int);
extern void *func_080DBA5C(void *);

u32 func_080EFCC0(void *task, Command080EFCC0 *command, State080EFCC0 *state)
{
    int effect_mode;

    switch (command->state) {
    case 0:
        state->flags = command->flags;
        state->object = command->object;
        state->actor = func_080DD748(state->object, &state->x, &state->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        effect_mode = state->flags & 1 ? 4 : 2;
        state->effect = func_080DCFE4(state->object, data_08399C1C, 12, 0,
                                    effect_mode | 8, task, 0);
        command->state++;
        break;
    case 0x101:
        state->effect = func_080DBA5C(state->effect);
        if (state->effect)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
