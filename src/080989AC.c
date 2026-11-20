#include "movement_tile.h"

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} PathStep;

extern s32 func_081492D0(PathGrid *grid, PathStep *path, u8 x, u8 y);
static inline Actor *object_at(Scene *scene, s8 x, s8 y)
{
    TileSearch search;

    search.match = 0;
    search.x = x;
    search.y = y;
    func_080C7CC0(scene->objects, func_0809ABB0, &search);
    return search.match;
}

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

/* Path candidate selection, 0x080989AC..0x08098A88 (220 bytes). */
s32 func_080989AC(Actor *actor, u8 x, u8 y, u8 range, PathStep *path)
{
    s32 count;
    s32 i;

    if (!func_08149384(actor->grid, x, y))
        return -1;
    if (object_at(actor->scene, x, y) != 0)
        return -1;
    count = func_081492D0(actor->grid, path, x, y);
    if (count <= 0)
        return -1;
    for (i = count - 1; i >= 0; i--) {
        if (can_stop(actor, path[i].x, path[i].y, range))
            break;
    }
    return i + 1;
}
