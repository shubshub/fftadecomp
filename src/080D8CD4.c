#include "ffta.h"

typedef struct TilePosition080D8CD4 {
    u8 unknown_00[0x0A];
    s8 x;
    s8 y;
} TilePosition080D8CD4;

extern TilePosition080D8CD4 *func_080A880C(void *object);
extern u8 func_080D8510(u8 x, u8 y);

static inline void get_coordinates(void *object, s16 *x, s16 *y)
{
    TilePosition080D8CD4 *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}

/* Complete [0x080D8CD4, 0x080D8D06): 50 bytes, 23 instructions. */
u8 func_080D8CD4(void *object)
{
    s16 x, y;

    get_coordinates(object, &x, &y);
    return func_080D8510(x, y);
}
