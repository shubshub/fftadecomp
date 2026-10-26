#include "ffta.h"

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080CCD50(u16 action, u8 selector);

/* Complete [0x080B448C, 0x080B44F8): 108 bytes, 50 instructions. */
u8 func_080B448C(u16 action, u16 parameter)
{
    u16 properties;
    s32 value;
    u8 result;

    if (action == 0) {
        if (parameter == 0)
            value = 1;
        else
            value = func_080CA7A4(parameter, 5);
        result = value;
    } else {
        properties = func_080CCD50(action, 4);
        if (properties & 0x80) {
            if (parameter == 0)
                value = 1;
            else
                value = func_080CA7A4(parameter, 5);
            result = value;
        } else if (properties & 0xC0) {
            result = func_080CCD50(action, 7) & 0x3F;
        } else {
            result = properties;
        }
    }
    return result;
}
