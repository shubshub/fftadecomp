#include "ffta.h"

/* Target: complete [0x0809A900, 0x0809A90C), 12 bytes, 4 instructions. */
typedef struct {
    u8 unknown_00[0x96];
    u8 value;
} State0200F390;

extern State0200F390 g_state_0200F390;

u8 func_0809A900(void)
{
    return g_state_0200F390.value;
}
