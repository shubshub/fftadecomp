#include "ffta.h"

typedef struct PathGrid PathGrid;
typedef struct ObjectList ObjectList;
typedef struct ListNode ListNode;
typedef struct {
    u8 unknown_00[0x10];
    ObjectList *objects;
} Scene;

typedef struct {
    u8 unknown_00[0x3c];
    PathGrid *grid;
    u8 unknown_40[0x40];
    Scene *scene;
} Actor;

typedef struct {
    u8 unknown_00[4];
    s8 x;
    s8 y;
    u8 unknown_06[2];
    Actor *match;
} TileSearch;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} PathStep;

extern u32 func_08149384(PathGrid *grid, u8 x, u8 y);
extern s32 func_081492D0(PathGrid *grid, PathStep *path, u8 x, u8 y);
extern s32 func_08097504(Actor *actor, s8 x, s8 y, u8 range);
extern s32 func_0809ABB0(const ListNode *node, TileSearch *search);
extern void func_080C7CC0(ObjectList *list, s32 (*visit)(const ListNode *, TileSearch *), TileSearch *search);

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
