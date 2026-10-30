#include "ffta.h"

/* Target 0x08020780..0x080207F4, 116 bytes:
 * f0b54f464646c0b481b0c578ed000179c90089464478e4008078c00080466f4602376846391cfdf7abfffdf763ff0004060cfdf765ff0004030c2c1968460021405e84420edd801985420bda4a46444610190024395f884204ddc818824201da012000e0002001b018bc9846a146f0bc02bc0847
 */
typedef struct {
    u8 unknown_00;
    u8 width;
    u8 height;
    u8 x;
    u8 y;
} Rectangle08020780;

typedef struct {
    s16 x;
    s16 y;
} Point08020780;

extern void func_0801E700(u16 *x, u16 *y);
extern u32 func_0801E674(void);
extern u16 func_0801E680(void);

u8 func_08020780(const Rectangle08020780 *rectangle)
{
    s32 x = rectangle->x * 8;
    s32 y = rectangle->y * 8;
    s32 width = rectangle->width * 8;
    s32 height = rectangle->height * 8;
    Point08020780 origin;
    u16 extent_x;
    u16 extent_y;
    u8 overlaps = 0;

    func_0801E700((u16 *)&origin.x, (u16 *)&origin.y);
    extent_x = (u16)func_0801E674();
    extent_y = func_0801E680();
    if (x + width > origin.x && x < origin.x + extent_x &&
        y + height > origin.y && y < origin.y + extent_y)
        overlaps = 1;
    return overlaps;
}
