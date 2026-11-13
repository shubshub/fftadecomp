#include "ffta.h"

// func_08044D90: 0x08044D90-0x08044E44 (180 bytes, 83 instructions)

typedef struct {
    s16 x;
    s16 y;
} Offset;

extern Offset func_0804BD4C(u8 a, u8 b, u8 index);
extern u16 func_08141860(s16 horizontal, s16 vertical);

u8 func_08044D90(u8 a, u8 b, u8 start)
{
    Offset sum;
    Offset from;
    Offset to;
    u8 i;

    sum.x = 0;
    sum.y = 0;
    for (i = 0; i <= 4; i++) {
        from = func_0804BD4C(a, b, start + i);
        if (from.x == 0 && from.y == 0)
            break;
        to = func_0804BD4C(a, b, start + i + 1);
        if (to.x == 0 && to.y == 0)
            break;
        sum.x += (s8)to.x - (s8)from.x;
        sum.y += (s8)to.y - (s8)from.y;
    }
    return ((func_08141860(sum.x, sum.y) >> 13) - 2) & 7;
}
