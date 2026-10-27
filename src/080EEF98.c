#include "ffta.h"

/* 0x080EEF98 .. 0x080EF11E: 390 bytes. */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 flags;
} Command080EEF98;

typedef struct {
    u8 flags;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *actor;
    void *effect_10;
    u32 unknown_14;
    void *effect_18;
    void *effect_1c;
    void *effect_20;
    void *effect_24;
    void *effect_28;
} State080EEF98;

extern const u8 data_088ED7EC[];
extern const u8 data_08399A04[];
extern const u8 data_0894D690[];
extern const u8 data_08949474[];
extern const u8 data_08399A1C[];
extern u16 g_control_flags_03000940;

extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void func_080D49FC(int, int, int, int, int);
extern void *func_080D4B64(int, const void *, int, int);
extern u32 func_080035A8(int);
extern void *func_080D6098(int, int, int, int, int, void *, const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DCFE4(void *, int, int, int, int, void *, int);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void *func_080D4D2C(void *, int);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080EEF98(void *task, Command080EEF98 *command, State080EEF98 *state)
{
    u32 set_mask;
    u32 clear_mask;
    u16 flags;
    int effect_mode;
    int display_flags;
    u8 had_effect;

    switch (command->state) {
    case 0:
        state->flags = command->flags;
        state->object = command->object;
        state->actor = func_080DD748(state->object, &state->x, &state->y, 0);
        break;
    case 0x100:
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->effect_10 = func_080D4B64(0, data_088ED7EC, 0x3bd, 6);
        set_mask = func_080035A8(2);
        flags = g_control_flags_03000940;
        flags |= set_mask;
        g_control_flags_03000940 = flags;
        state->effect_18 = func_080D6098(state->x, state->y, 0, 1, 1,
                                       &state->unknown_14, data_08399A04, task);
        state->effect_1c = func_080D3E9C(data_0894D690, task);
        state->effect_20 = func_080D4704(data_08949474, task);
        effect_mode = state->flags & 1 ? 4 : 2;
        state->effect_24 = func_080DCFE4(state->object, 0, 12, 0, effect_mode, task, 0x37);
        display_flags = state->flags & 1 ? 16 : 8;
        state->effect_28 = func_080DFD8C(data_08399A1C, 1, display_flags | 4, 0, task);
        command->state++;
        break;
    case 0x101:
        state->effect_10 = func_080D4D2C(state->effect_10, 0);
        if (state->effect_10)
            break;
        state->effect_1c = func_080D3F08(state->effect_1c);
        if (state->effect_1c)
            break;
        had_effect = state->effect_20 != 0;
        state->effect_20 = func_080D4774(state->effect_20);
        if (state->effect_20)
            break;
        if (had_effect) {
            clear_mask = func_080035A8(2);
            g_control_flags_03000940 &= ~clear_mask;
        }
        state->effect_18 = func_080D6134(state->effect_18);
        if (state->effect_18)
            break;
        command->state++;
        break;
    case 0x102:
        state->effect_24 = func_080DBA5C(state->effect_24);
        if (state->effect_24)
            break;
        command->state = 2;
        break;
    }
    return 0;
}
