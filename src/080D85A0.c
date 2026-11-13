#include "ffta.h"

// Complete target: [0x080D85A0, 0x080D8604), 100 bytes.
extern void func_0801CDA4(s16 *x, s16 *y, s16 *z);
extern void func_0801C918(s16 x, s16 y, s16 z, s16 *screen_x,
                         s16 *screen_y, s16 *depth);
extern int func_0801BB94(s16 x, s16 y, int mode, int effect, int option);

static inline int is_visible(s16 x, s16 y)
{
    u32 result = (u16)func_0801BB94(x, y, 4, 0x10, 4);

    return -result >> 31;
}

int func_080D85A0(void)
{
    s16 world_x, world_y, world_z;
    s16 screen_x, screen_y, depth;

    func_0801CDA4(&world_x, &world_y, &world_z);
    func_0801C918(world_x, world_y, world_z, &screen_x, &screen_y, &depth);
    screen_x -= 0x78;
    screen_y -= 0x50;
    return is_visible(screen_x, screen_y);
}
