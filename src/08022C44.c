#include "ffta.h"

typedef struct {
    u16 pressed;
    u16 held;
    u16 repeated;
} InputState08022C44;

typedef struct {
    u8 unknown_00[0x0F];
    u8 timer;
} State08022C44;

extern InputState08022C44 data_03000000;
extern State08022C44 g_state_0200F390;
extern u32 func_08022C64(void);

/* 0x08022C44 - 32 bytes.
 * Target: 00b5054a0021118091800449c87300f007f801bc004700000000000390f30002
 */
void func_08022C44(u8 timer)
{
    data_03000000.pressed = 0;
    data_03000000.repeated = 0;
    g_state_0200F390.timer = timer;
    func_08022C64();
}
