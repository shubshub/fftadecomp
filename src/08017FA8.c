#include "ffta.h"

typedef struct {
    const u8 *graphics;
    s16 x;
    s16 y;
} DrawOrigin;

/* 08017FA8..08017FB0: 8 bytes. */
void func_08017FA8(void *object, const u8 *graphics, s32 x, s32 y)
{
    DrawOrigin *origin = object;

    origin->graphics = graphics;
    origin->x = x;
    origin->y = y;
}
