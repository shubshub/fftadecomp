#include "ffta.h"

/* 0x080F2CDC .. 0x080F2E3E: 354 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 variant;
} Command080F2CDC;

typedef struct {
    s16 x;
    s16 y;
    u8 variant;
    u8 unknown_05[3];
    u32 unknown_08;
    void *effect_0c;
    void *effect_10;
    void *effects[2];
    void *object;
    void *effect_20;
} State080F2CDC;

extern const u8 data_0839A880[];
extern const u8 data_088F4E9C[];
extern const u8 data_0894DB6C[];
extern const u8 data_0894B914[];
extern const u8 data_0894C528[];
extern const u8 data_0894C578[];
extern const u8 data_0894C424[];
extern const u8 data_0894B964[];
extern const u8 data_0839A8E0[];
extern const u8 data_0839A8D8[];
extern u16 g_control_flags_03000940;

extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void **, int);
extern u32 func_080035A8(int);

u32 func_080F2CDC(void *task, Command080F2CDC *command, State080F2CDC *state)
{
    u32 mask;

    switch (command->state) {
    case 0:
        state->variant = command->variant;
        state->object = command->object;
        state->x = 120;
        state->y = 128;
        if (state->variant != 7)
            state->y = 96;
        break;
    case 0x100:
        state->effect_0c = func_080D6098(state->x, state->y, 0, 1, 1,
                                       &state->unknown_08, data_0839A880, task);
        func_080D7220(data_088F4E9C, 0, 2, state->x, state->y, 0);
        state->effect_10 = func_080D3E9C(data_0894DB6C, task);
        if (state->variant == 7) {
            state->effects[0] = func_080D4704(data_0894B914, task);
            state->effects[1] = func_080D4704(data_0894B964, task);
        } else if (state->variant == 8) {
            state->effects[0] = func_080D4704(data_0894C528, task);
            state->effects[1] = func_080D4704(data_0894C578, task);
        } else {
            state->effects[0] = func_080D4704(data_0894C424, task);
            state->effects[1] = func_080D4704(data_0894B964, task);
        }
        if (state->variant == 9)
            state->effect_20 = func_080DFD8C(data_0839A8E0, 1, 4, 0, task);
        else
            state->effect_20 = func_080DFD8C(data_0839A8D8, 1, 4, 0, task);
        command->state++;
        break;
    case 0x101:
        state->effect_0c = func_080D6134(state->effect_0c);
        if (state->effect_0c)
            break;
        state->effect_10 = func_080D3F08(state->effect_10);
        if (state->effect_10)
            break;
        if (!func_080D48DC(state->effects, 2))
            break;
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        command->state++;
        break;
    case 0x102:
        command->state = 2;
        break;
    }
    return 0;
}
