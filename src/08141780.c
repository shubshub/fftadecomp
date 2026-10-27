#include "ffta.h"

/* Complete [0x08141780, 0x081417E8): 104 bytes, 32 instructions. */
extern u8 data_020084D8;
extern u8 data_0200F2A0[];
extern void func_08146120(void *, u16, u16);

void func_08141780(float volume)
{
    if (volume < 0.0156)
        volume = 0.0156f;

    if (data_020084D8 & 1) {
        u16 scaled = (u32)(volume * 256.0f);

        func_08146120(data_0200F2A0, 0xFFFF, scaled ? scaled : 1);
    }
}
