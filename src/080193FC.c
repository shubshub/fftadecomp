#include "ffta.h"

extern u8 func_080CECF4(void);
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

u32 func_080193FC(u8 *destination, u8 code)
{
    u8 count = func_080CECF4();

    if (count != 30) {
        if (count < 10)
            destination += func_08018CB8(destination, 8);
        func_08018ABC(destination, count);
    }
    return 0;
}
