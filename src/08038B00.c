#include "ffta.h"

extern const u16 data_08955230[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080355A0(const u16 *source, u16 *destination,
                         u32 height, u16 width, u16 stride);

/* Complete [0x08038B00, 0x08038B2C): 44 bytes, 17 instructions. */
void func_08038B00(void)
{
    u16 *destination = func_0808B8E4(0, 1, 24, 8);

    func_080355A0(data_08955230, destination, 4, 4, 32);
}
