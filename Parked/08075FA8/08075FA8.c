#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1cec];
    u16 displayed_first;
    u16 displayed_second;
    u16 displayed_third;
    u16 previous_first;
    u16 previous_second;
    u16 previous_third;
} StatDisplay;

typedef struct {
    u8 unknown_000[0x10c];
    u8 color;
} Display;

extern StatDisplay *data_03002818;
extern Display data_030009E0;
extern void func_080CA2E8(void *object);
extern s32 func_080CA394(void *object);
extern s32 func_080CA610(void *object);
extern s32 func_080CA5C4(void *object);
extern u16 *func_0808B8E4(u32 window, u32 layer, s32 x, s32 y);
extern void func_080899AC(u16 *position, u16 color, u16 spacing, u16 value,
                         u16 digits, u16 alignment, u16 tile);

/* 0x08075FA8..0x0807614C: 420 bytes, 173 instructions. */
void func_08075FA8(void *object, u32 neutral)
{
    u16 tile;
    u16 difference;
    u16 *position;

    func_080CA2E8(object);
    difference = func_080CA394(object) - data_03002818->previous_first;
    if (neutral)
        tile = 0xd000;
    else if ((s16)difference < 0)
        tile = 0xa000;
    else if ((s16)difference > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    position = func_0808B8E4(3, 1, 6, 1);
    func_080899AC(position, data_030009E0.color, 100, data_03002818->displayed_first + (s16)difference, 1, 0, tile);

    difference = func_080CA610(object) - data_03002818->previous_second;
    if (neutral)
        tile = 0xd000;
    else if ((s16)difference < 0)
        tile = 0xa000;
    else if ((s16)difference > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    position = func_0808B8E4(0, 1, 6, 9);
    func_080899AC(position, 32, 120, data_03002818->displayed_second + (s16)difference, 1, 0, tile);

    difference = func_080CA5C4(object) - data_03002818->previous_third;
    if (neutral)
        tile = 0xd000;
    else if ((s16)difference < 0)
        tile = 0xa000;
    else if ((s16)difference > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    position = func_0808B8E4(3, 1, 12, 2);
    func_080899AC(position, data_030009E0.color, 120, data_03002818->displayed_third + (s16)difference, 3, 0, tile);
}
