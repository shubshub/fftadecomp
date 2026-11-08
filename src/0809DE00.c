#include "ffta.h"

typedef struct {
    u16 x;
    u16 unknown_02;
    u16 y;
} QueryPosition;

typedef struct {
    s32 top, bottom, left, right;
    u8 result;
} QueryRegion;

extern QueryPosition data_0200F3B8;
extern const QueryRegion data_08394364[];
extern u8 func_0801CC18(u8, u8);
extern void func_0801C984(s16, s16, s16, s16 *, s16 *);

/* Target: [0x0809DE00, 0x0809DE94), 148 bytes including literals. */
u8 func_0809DE00(void)
{
    s16 x, y;
    u32 i;

    func_0801C984(data_0200F3B8.x * 32 + 16,
                   func_0801CC18(data_0200F3B8.x, data_0200F3B8.y) * 16,
                   data_0200F3B8.y * 32 + 16, &x, &y);
    y -= 12;
    for (i = 0; i < 4; i++) {
        if (data_08394364[i].left < x && data_08394364[i].right > x &&
            data_08394364[i].top < y && data_08394364[i].bottom > y)
            return data_08394364[i].result;
    }
    return 128;
}
