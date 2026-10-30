#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1199];
    u8 mode;
    u8 phase;
    u8 unknown_119B;
    u8 timer;
    u8 unknown_119D[7];
    u16 amount;
} State;

typedef struct {
    u8 unknown_00[0x1F64];
    u32 funds;
} GlobalState;

extern State *data_0200F448;
extern GlobalState g_state_02000000;
extern u8 data_030008B0[];
extern void func_08029F18(s32 amount, void *context, u32 zero, u32 duration, u32 mode);
extern void func_08013364(void);

/* 0x0805EA0C..0x0805EAA8 - 156 bytes including literal pools. */
void func_0805EA0C(void)
{
    if (++data_0200F448->timer == 1) {
        func_08029F18(-data_0200F448->amount, data_030008B0, 0, 20, 17);
    } else if (data_0200F448->timer > 10) {
        data_0200F448->timer = 0;
        g_state_02000000.funds -= data_0200F448->amount;
        func_08013364();
        data_0200F448->phase = 17;
        data_0200F448->mode = 2;
    }
}
