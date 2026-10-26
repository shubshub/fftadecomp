#include "ffta.h"

typedef struct {
    s8 x;
    s8 y;
} MovingPanel;

extern u8 data_030008B0[];
extern u8 data_03000990[];
extern void func_0802B2E8(void *tilemap, u8 x, u8 y, u8 width, u8 height);
extern void func_0806F33C(MovingPanel *panel, s8 x, s8 y);

/* Complete target: [0x0806F46C, 0x0806F568), 252 bytes, 111 instructions. */
u32 func_0806F46C(MovingPanel *panel, u8 target)
{
    u8 old_x = panel->x;
    s8 delta;
    s8 previous;

    if (panel->x == (s8)target)
        return 1;
    delta = (s8)target - old_x;
    previous = panel->x;
    if (delta > 0) {
        s8 end;
        s8 width;

        panel->x += 4;
        if (panel->x >= (s8)target)
            panel->x = target;
        end = panel->x;
        if (panel->x > 30)
            end = 30;
        width = end - previous;
        if (width > 0) {
            func_0802B2E8(data_030008B0, previous, panel->y, width, 3);
            func_0802B2E8(data_03000990, previous, panel->y, width, 3);
        }
    } else {
        panel->x -= 4;
        if (panel->x < (s8)target)
            panel->x = target;
        if (panel->x + 14 <= 29) {
            s32 end = previous + 14;
            s32 width;

            if (end > 30)
                end = 30;
            width = (s8)end - 14 - (u8)panel->x;
            func_0802B2E8(data_030008B0, panel->x + 14, panel->y, width, 3);
            func_0802B2E8(data_03000990, panel->x + 14, panel->y, width, 3);
        }
    }
    func_0806F33C(panel, panel->x, panel->y);
    return 0;
}
