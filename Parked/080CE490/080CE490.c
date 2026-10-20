#include "ffta.h"

void func_080CD774(u8 *data, u8 first, u8 second);

void func_080CE490(u8 *data, u8 enabled)
{
    u8 first = data[0xDA];
    u8 second = data[0xDB];
    u8 blocked = 0x80;

    if (!(first & blocked) && !(second & blocked)) {
        if (enabled) {
            first += 3;
            if (first > 6)
                first = 6;
        } else {
            second += 3;
            if (second > 6)
                second = 6;
        }
        func_080CD774(data, first, second);
    }
}
