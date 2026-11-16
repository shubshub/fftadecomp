#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

typedef struct {
    u8 unknown_00[0x10];
    u8 selection;
    u8 count;
} ChoiceState;

typedef struct {
    u8 active;
    u8 flags;
} IndicatorState;

typedef struct {
    u8 unknown_00[0x5C];
    IndicatorState *indicators;
} MenuState;

extern InputState data_03000000;
extern MenuState g_state_0200F390;
extern ChoiceState g_state_020020D0;
extern void func_08141570(s32 player_id, u16 song_id);
extern void func_08141540(u16 song_id);
extern void func_08013364(void);
extern void func_08011B30(u8 kind, u16 entry);

/* Complete target: [0x08023DBC, 0x08023E88), 204 bytes. */
u8 func_08023DBC(void)
{
    u8 changed = 0;
    u16 buttons = data_03000000.pressed;
    IndicatorState *state = g_state_0200F390.indicators;

    if (buttons & 2) {
        func_08141570(1, 0x69);
        func_08013364();
        state->active = 0;
        state->flags |= 1;
        return 1;
    }
    if (buttons & 1) {
        func_08141540(0x64);
        func_08013364();
        state->active = 0;
        state->flags |= 1;
        return 1;
    }
    if (buttons & 0x10) {
        if (g_state_020020D0.count == 1)
            return 0;
        changed = 1;
        if (g_state_020020D0.selection < g_state_020020D0.count - 1)
            g_state_020020D0.selection++;
        else
            g_state_020020D0.selection = 0;
    } else if (buttons & 0x20) {
        if (g_state_020020D0.count == 1)
            return 0;
        changed = 1;
        if (g_state_020020D0.selection != 0)
            g_state_020020D0.selection--;
        else
            g_state_020020D0.selection = g_state_020020D0.count - 1;
    }
    if (changed) {
        func_08141540(0x6D);
        func_08013364();
        func_08011B30(9, g_state_020020D0.selection);
        return 1;
    }
    return 0;
}
