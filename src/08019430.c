#include "ffta.h"

extern u16 func_080CE8A8(void);
extern u32 func_080CED2C(void);
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

u32 func_08019430(u8 *destination, u8 code)
{
    u16 count = func_080CE8A8();
    u16 maximum = func_080CED2C();

    if (count != maximum) {
        if (count < 100)
            destination += func_08018CB8(destination, 8);
        if (count < 10)
            destination += func_08018CB8(destination, 8);
        func_08018ABC(destination, count);
    }
    return 0;
}
