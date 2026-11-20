#include "movement_tile.h"

extern s32 func_080CA3EC(const void *unit);

/* The same tile lookup is out of line at 0x08099644. */
static inline Actor *object_at(Scene *scene, s8 x, s8 y)
{
    TileSearch search;

    search.match = 0;
    search.x = x;
    search.y = y;
    func_080C7CC0(scene->objects, func_0809ABB0, &search);
    return search.match;
}

/* The explicit-range check also appears at 0x08099F58. */
static inline s32 can_stop(Actor *actor, s8 x, s8 y, u8 range)
{
    Actor *object;
    if (!func_08097504(actor, x, y, range))
        return 0;
    object = object_at(actor->scene, x, y);
    if (object != 0 && object != actor)
        return 0;
    return 1;
}

/* Complete [0x08099FB0, 0x0809A018), 104 bytes. */
s32 func_08099FB0(Actor *actor, s32 x, s32 y)
{
    return can_stop(actor, x, y, (u32)func_080CA3EC(actor->unit) / 10);
}
