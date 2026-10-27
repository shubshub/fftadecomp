#include "ffta.h"

struct TileRegion0804ED44 {
    u8 unknown_00[0x28];
};

struct Menu0804ED44 {
    u8 unknown_00[0x250];
    struct TileRegion0804ED44 region;
};

extern struct Menu0804ED44 *data_0201F54C;
extern u8 func_08017180(struct TileRegion0804ED44 *region);

u8 func_0804ED44(void)
{
    return func_08017180(&data_0201F54C->region);
}
