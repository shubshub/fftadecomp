#include "ffta.h"

typedef void (*BufferCopier0802D7A0)(void *destination, const void *source,
                                    u32 size);

extern u8 g_state_02002FC4[];
extern u16 data_02003C34[4];
extern BufferCopier0802D7A0 data_0836D4BC[];
extern u8 func_0802D764(void);

/* Complete [0x0802D7A0, 0x0802D822): 130 bytes, 55 instructions. */
void func_0802D7A0(void)
{
    u8 *state = g_state_02002FC4;
    s32 count = func_0802D764();

    if (count != 0) {
        s32 removed = 0;
        s32 index = 0;
        while (index < count) {
            u16 *source = (u16 *)(state + 0xC72) + index;
            u16 *destination = data_02003C34 + index;
            u16 value = *destination;

            if (value == 0) {
                removed++;
                data_0836D4BC[0](destination, source,
                                 (4 - (index + removed)) * sizeof(u16));
                data_02003C34[4 - removed] = value;
            } else {
                index++;
            }
        }
    }
}
