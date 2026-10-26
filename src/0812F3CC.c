#include "ffta.h"

/* Target: complete [0x0812F3CC, 0x0812F410), 68 bytes including literals. */
typedef struct {
    u8 unknown_00[0x2190];
    u8 mode;
} State0812F3CC;

extern State0812F3CC g_state_02000000;
extern u8 func_080C95A8(u16);
extern s32 func_080C7EA4(const void *, u32);

u8 func_0812F3CC(const void *object)
{
    if (func_080C95A8(13) != 1 &&
        (g_state_02000000.mode == 22 || g_state_02000000.mode == 26) &&
        func_080C7EA4(object, 1) == 13)
        return 1;
    return 0;
}
