#include "ffta.h"

typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outerWidth;
    u8 unknown_13;
    u16 value;
    u8 stride;
    u8 mode;
    u16 first;
    u16 last;
    u8 flags;
    u8 unknown_1D[2];
    u8 alignment;
    u16 width;
    u16 height;
    s16 expectedWidth;
    s16 expectedHeight;
} TileRegion;

typedef struct {
    u8 unknown_00[0x10];
    TileRegion window;
} Context080603F4;

extern u8 func_08017180(TileRegion *region);

/* Complete target: [0x080603F4, 0x08060404), 16 bytes.
 * Callers 0x0805FB9C and 0x0806094C pass a context with its window at +0x10.
 */
u8 func_080603F4(Context080603F4 *context)
{
    return func_08017180(&context->window);
}
