#include "ffta.h"

typedef struct Unit Unit;
extern u32 func_080CCD50(u16 identifier, u8 selector);
extern u8 func_080CD50C(const Unit *unit);
extern s32 func_080CA7A4(u16 identifier, u8 selector);

/* Target: complete [0x0812F48C, 0x0812F528), 156 bytes, 72 instructions. */
s16 func_0812F48C(const Unit *unit, s16 value, u16 identifier, u16 fallback)
{
    s32 result = value;
    u32 category = identifier == 0 ? 0 :
        (func_080CCD50(identifier, 29) != 0 ? 0 : 1);

    switch (func_080CD50C(unit)) {
    case 1:
        if (category == 0)
            result = (result * 307) >> 8;
        break;
    case 3:
        if (category == 1)
            result = (result * 307) >> 8;
        break;
    case 4:
        if (identifier != 0 && func_080CCD50(identifier, 2))
            result = (result * 332) >> 8;
        break;
    case 7:
        if (identifier == 0 && fallback != 0 &&
            func_080CA7A4(fallback, 6) == 1)
            result = (result * 307) >> 8;
        break;
    }
    return result;
}
