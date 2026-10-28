#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 *object;
} DisplayState;

extern DisplayState data_030008B0;
extern void func_08016A98(void *object, u32 first, u32 second, u32 third, u32 fourth);

/* Complete target: [0x0806149C, 0x080614C4), 40 bytes, 17 instructions. */
void func_0806149C(u8 enabled)
{
    if (enabled)
        func_08016A98(data_030008B0.object + 0x74, 3, 2, 0, 0x20);
}
