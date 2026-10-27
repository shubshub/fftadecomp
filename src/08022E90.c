#include "ffta.h"

typedef struct Transition08022E90 {
    u8 unknown_00[0x18];
} Transition08022E90;

typedef struct State08022E90 {
    u8 unknown_00[0x0D];
    u8 half_duration;
    u8 unknown_0E[0x36];
    Transition08022E90 transition;
    void *buffer;
} State08022E90;

typedef void (*PaletteInitializer08022E90)(void *destination, u32 size);

extern State08022E90 g_state_0200F390;
extern u16 data_03003860[512];
extern PaletteInitializer08022E90 const g_callbacks_0836D4B8[];
extern void func_08022E24(void);
extern void func_08007620(Transition08022E90 *transition,
                        s16 start_x, s16 start_y, s16 end_x, s16 end_y);

/* Complete [0x08022E90, 0x08022F00): 112 bytes, 45 instructions. */
void func_08022E90(u16 duration, u8 mode)
{
    State08022E90 *state = &g_state_0200F390;

    state->half_duration = duration >> 1;
    switch (mode) {
    case 15:
        g_callbacks_0836D4B8[0](data_03003860, sizeof(data_03003860));
        func_08007620(&state->transition, duration, 0, 0, duration);
        break;
    case 16:
        if (!state->buffer) {
            func_08022E24();
            func_08007620(&state->transition, 0, 0, duration, duration);
        }
        break;
    }
}
