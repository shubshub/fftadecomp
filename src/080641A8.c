#include "ffta.h"

typedef struct {
    ScriptState script;
    u8 unknown_68[4];
    u8 queue[0x60];
} MenuState;

extern MenuState *data_0200F450;
extern void func_080C71B4(u16 request);
extern void func_080C73C4(u32 queue, u32 context, u16 width, u8 mode);

void func_080641A8(void)
{
    MenuState *state;

    func_080C71B4(1);
    state = data_0200F450;
    func_080C73C4((u32)state->queue, state->script.unknown_5c, 264, 2);
    data_0200F450->script.current = 45;
}
