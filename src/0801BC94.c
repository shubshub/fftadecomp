#include "ffta.h"

/* 0801BC94..0801BCF8: 100 bytes. */
struct Interpolation {
    s32 value;
    u8 unknown_04[0x28];
};

struct CameraState {
    u8 unknown_00[0x34];
    u8 moving;
    u8 movement_mode;
    u8 unknown_36[6];
    struct Interpolation horizontal;
    struct Interpolation vertical;
};

extern struct CameraState g_state_02007F40;
extern void func_0801B898(void);
extern void func_080076A0(struct Interpolation *interpolation);
extern void func_0801E5E0(s16 x, s16 y);
extern u32 func_08007880(struct Interpolation *interpolation);

void func_0801BC94(void)
{
    struct CameraState *state = &g_state_02007F40;

    if (state->moving == 0)
        return;
    if (state->movement_mode == 1) {
        func_0801B898();
        return;
    }
    func_080076A0(&state->horizontal);
    func_080076A0(&state->vertical);
    func_0801E5E0((s16)state->horizontal.value, (s16)state->vertical.value);
    if (func_08007880(&state->horizontal) != 0 &&
        func_08007880(&state->vertical) != 0)
        state->moving = 0;
}
