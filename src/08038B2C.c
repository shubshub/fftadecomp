#include "ffta.h"

extern const u16 data_089551F4[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080355A0(const u16 *source, u16 *destination,
                         u32 height, u16 width, u16 stride);

/* Complete [0x08038B2C, 0x08038B58): 44 bytes, 17 instructions. */
void func_08038B2C(void)
{
    u16 *destination = func_0808B8E4(0, 1, 4, 18);

    func_080355A0(data_089551F4, destination, 3, 10, 32);
}
