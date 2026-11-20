#include "ffta.h"

typedef struct PathGrid PathGrid;
typedef struct ObjectList ObjectList;
typedef struct ListNode ListNode;
typedef struct {
    u8 unknown_00[0x10];
    ObjectList *objects;
} Scene;

typedef struct {
    void *unit;
    u8 unknown_04[0x16];
    u8 phase;
    u8 range;
    u8 unknown_1c[0x20];
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

extern s32 func_08097504(Actor *actor, s8 x, s8 y, u8 range);
extern s32 func_0809ABB0(const ListNode *node, TileSearch *search);
extern void func_080C7CC0(ObjectList *list, s32 (*visit)(const ListNode *, TileSearch *), TileSearch *search);

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

extern u32 func_08149368(PathGrid *grid);
extern u8 func_0801D8B8(void);
extern void func_0801D938(void);
extern s32 func_080CA3EC(const void *unit);
extern void func_0801D624(u8 x, u8 y, u8 mode);
extern void func_0801D918(void);

/* 0x08099FB0 derives the range from the unit before checking the tile. */
static inline s32 reachable(Actor *actor, s8 x, s8 y)
{
    return can_stop(actor, x, y, (u32)func_080CA3EC(actor->unit) / 10);
}

/* Movement overlay update, 0x08098A88..0x08098BAE (294 bytes). */
s32 func_08098A88(Actor *actor)
{
    s32 x, y;

    if (!func_08149368(actor->grid) || !func_0801D8B8())
        return 0;
    switch (actor->phase) {
    case 0:
        /* The setup arm reads display readiness again at 0x08098AB6. */
        if (func_0801D8B8()) {
            func_0801D938();
            actor->phase = 1;
            return 0;
        }
        break;
    case 1:
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (reachable(actor, x, y)
                    && !object_at(actor->scene, x, y))
                    func_0801D624(x, y, 1);
            }
        }
        actor->phase = 2;
        actor->range = (u32)func_080CA3EC(actor->unit) / 10;
        func_0801D918();
        return 0;
    }
    return 1;
}
