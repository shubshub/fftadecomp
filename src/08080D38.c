#include "ffta.h"

typedef struct {
    u8 unknown_00[0xd6];
    u16 value;
} DisplayValue08080D38;

extern u16 *func_0808B8E4(u32 window, u32 plane, s32 x, s32 y);

/* Complete target [0x08080D38, 0x08080D74): 60 bytes, 25 instructions. */
u32 func_08080D38(const DisplayValue08080D38 *object)
{
    u32 result;

    if (object->value < 10) {
        *func_0808B8E4(2, 1, 26, 5) = 0;
        result = 0;
    } else {
        *func_0808B8E4(2, 1, 26, 5) = 0xd090;
        result = 1;
    }
    return result;
}
