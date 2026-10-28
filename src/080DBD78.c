#include "ffta.h"

extern void func_0801C9F0(s16 x, s16 y, s16 z,
                         s16 *tile_x, s16 *tile_y, s16 *tile_z);

/* Complete [0x080DBD78, 0x080DBDA0): 40 bytes, 19 instructions. */
void func_080DBD78(const Struct080DBD5C *source,
                   s16 *tile_x, s16 *tile_y, s16 *tile_z)
{
    func_0801C9F0(source->x, source->y, source->z, tile_x, tile_y, tile_z);
}
