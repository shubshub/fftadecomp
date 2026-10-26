#include "ffta.h"

/* 0x080CC9A0..0x080CC9EE: 78 bytes. */
extern const u8 *func_080CCCF0(u8 selector);

u8 func_080CC9A0(u8 selector, u16 value)
{
    u8 i;

    func_080CCCF0(selector);
    for (i = 0; i <= 30; i++) {
        const u8 *list = func_080CCCF0(selector);
        u16 entry;

        if (list == 0 || i == 0)
            entry = 0;
        else {
            const u8 *item = list + (i - 1) * 2;
            u8 low = item[4];
            u8 high = item[5];
            entry = (high << 8) | low;
        }
        if (entry == value)
            return 1;
    }
    return 0;
}
