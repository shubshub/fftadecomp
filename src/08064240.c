#include "ffta.h"

typedef struct {
    u16 current;
    u8 unknown_02[0x56];
    u32 selection;
    u8 unknown_5C[0x10];
    u8 queue[0x60];
} MenuState;

extern u8 data_02003C34[];
extern MenuState *data_0200F450;
extern void func_080C71B4(u16 request);
extern void func_080C73C4(u32 queue, u32 context, u16 width, u8 mode);

void func_08064240(void)
{
    MenuState *state;

    func_080C71B4(1);
    state = data_0200F450;
    func_080C73C4((u32)state->queue, (u32)data_02003C34, 8, state->selection == 0);
    data_0200F450->current = 45;
}
