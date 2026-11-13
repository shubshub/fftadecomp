#include "ffta.h"

// func_080BD1EC - 0x080BD1EC..0x080BD326, 314 bytes (118 instructions).
// Steps the mode-selection state machine set up by func_080BD14C.

typedef struct {
    u16 mode;
    u8 result;
    s8 flag;
    u16 selection;
    u16 count;
    u16 options[34];
} OptionState;

extern u8 g_state_02000000[];

extern void func_0802966C(void);
extern void func_08029544(u32 operation);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013364(void);
extern u32 func_0813B0D4(u8 selector, void *buffer);

static inline void push_option(OptionState *state, u16 option)
{
    state->selection = option;
    state->options[state->count++] = option;
}

static inline void pop_option(OptionState *state)
{
    state->selection = state->options[--state->count];
}

u8 func_080BD1EC(OptionState *state)
{
    switch (state->selection) {
    case 11:
        func_0802966C();
        if (state->flag == 0) {
            state->result = 1;
            state->selection = 0;
            break;
        }
        pop_option(state);
        break;
    case 10:
        if (state->flag != 0)
            state->mode = 9;
        else
            state->mode = 10;
        state->selection = 1;
        break;
    case 6:
        state->mode = 7;
        state->selection = 1;
        break;
    case 7:
        state->flag = func_0813B0D4(2, g_state_02000000);
        func_08013364();
        pop_option(state);
        break;
    case 1:
        func_08029544((u8)state->mode);
        state->selection = 2;
        break;
    case 2:
        if (func_08011860())
            pop_option(state);
        break;
    case 5:
        if (func_08011860()) {
            func_0802966C();
            pop_option(state);
        }
        break;
    case 3:
        state->mode = 6;
        push_option(state, 4);
        state->selection = 1;
        break;
    case 4:
        if (func_08013380()) {
            state->selection = 0;
            state->result = 1;
        } else {
            pop_option(state);
        }
        func_0802966C();
        break;
    case 8:
        state->result = 3;
        pop_option(state);
        break;
    case 9:
        if (func_08013380() == 0)
            state->result = 3;
        else
            state->result = 2;
        pop_option(state);
        func_0802966C();
        break;
    case 0:
        return state->result;
    }
    return 0;
}
