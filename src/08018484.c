#include "ffta.h"

u8 func_080184D0(u8 code);

static inline u8 is_special_code(u8 code)
{
    u8 special = 0;

    if (code == 3 || code == 4 || code == 10 || code == 11 ||
        code == 12 || code == 13 || code == 15 || code == 14)
        special = 1;
    return special;
}

u8 func_08018484(u8 code)
{
    u8 accepted = 0;

    if (is_special_code(code) || func_080184D0(code))
        accepted = 1;
    return accepted;
}
