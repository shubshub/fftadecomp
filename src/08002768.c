#include "ffta.h"

// Complete [0x08002768, 0x080027B8): 80 bytes, 26 instructions.
// Clears EWRAM [0x02000000, 0x0203FC00) (255 KiB) and IWRAM below 0x03007C00 with CpuSet
// fills, then copies the code block 0x08A38A2C..0x08A38ADC into IWRAM at
// 0x03005E78.  The two RAM bases are built from immediates (movs/lsls), so
// they are address constants in the source rather than named objects.
extern u8 data_03005E78[];
extern const u8 data_08A38A2C[];
extern const u8 data_08A38ADC[];
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08002768(void)
{
    /* One-element fill sources for the two CpuSet fills. */
    u32 word_fill[1];
    u16 half_fill[1];
    u32 size;

    word_fill[0] = 0;
    func_0814186C(word_fill, (void *)0x02000000, 0x0500FF00);
    half_fill[0] = 0;
    func_0814186C(half_fill, (void *)0x03000000, 0x01003E00);
    size = data_08A38ADC - data_08A38A2C;
    func_0814186C(data_08A38A2C, data_03005E78, (size >> 1) & 0x1fffff);
}
