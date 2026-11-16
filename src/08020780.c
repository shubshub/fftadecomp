#include "ffta.h"

/* Complete [0x08020780, 0x080207F4): 116 bytes, 55 instructions, no literal
 * pool.
 * f0b54f464646c0b481b0c578ed000179c90089464478e4008078c00080466f4602376846
 * 391cfdf7abfffdf763ff0004060cfdf765ff0004030c2c1968460021405e84420edd8019
 * 85420bda4a46444610190024395f884204ddc818824201da012000e0002001b018bc9846
 * a146f0bc02bc0847
 *
 * Returns 1 when the window's rectangle - its x, y and dimensions in tiles,
 * times 8 - overlaps the area that starts at the position func_0801E700
 * reports and has the sizes func_0801E674 and func_0801E680 return, else 0.
 */

typedef struct {
    u8 layer;
    u8 dimensions[2];
    u8 x;
    u8 y;
} MapWindow;

extern void func_0801E700(u16 *x, u16 *y);
extern u32 func_0801E674(void);
extern u16 func_0801E680(void);

u8 func_08020780(const MapWindow *window)
{
    s16 x = window->x * 8;
    s16 y = window->y * 8;
    s16 width = window->dimensions[0] * 8;
    s16 height = window->dimensions[1] * 8;
    s16 origin_x;
    s16 origin_y;
    u16 extent_x;
    u16 extent_y;

    func_0801E700((u16 *)&origin_x, (u16 *)&origin_y);
    extent_x = func_0801E674();
    extent_y = func_0801E680();
    if (x + width > origin_x && x < origin_x + extent_x &&
        y + height > origin_y && y < origin_y + extent_y)
        return 1;
    return 0;
}
