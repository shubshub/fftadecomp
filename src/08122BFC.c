#include "ffta.h"

/* Target: complete [0x08122BFC, 0x08122C28), 44 bytes including literals. */
typedef struct {
    u8 unknown_00[0x96];
    u16 mode;
} State08122BFC;

extern State08122BFC g_state_0200F390;
extern void func_08126AA8(void *, const u8 *, u32);

u32 func_08122BFC(void *context, const u8 *instruction)
{
    u32 result;

    if (g_state_0200F390.mode != 3) {
        func_08126AA8(context, instruction, 0);
        result = 0x115;
    } else {
        result = 0x110;
    }
    return result;
}
