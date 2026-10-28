#include "ffta.h"

extern const u8 data_083E105C[];
extern const u8 *func_080071A8(const u8 *table, u16 index);
extern u32 func_0800543C(void *destination, const void *source);

/* Complete [0x080CB8B4, 0x080CB8D4): 32 bytes, 12 instructions. */
u32 func_080CB8B4(void *destination, u8 index)
{
    const u8 *source = func_080071A8(data_083E105C, index);

    return func_0800543C(destination, source);
}
