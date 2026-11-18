#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

typedef struct {
    Unit *unit;
    Unit *related;
} SceneObject;

typedef struct {
    Unit *source;
    Unit *target;
    Unit *result;
    u8 unknown_0C[0x1A];
    u16 flags;
} Action;

extern void *func_08096D7C(void);
struct Owner;
struct Object;
extern struct Object *func_08099560(struct Owner *scene, u32 unit_key);
extern u32 func_08098E7C(void *scene, void *source, void *target, void *related,
                        u8 *x, u8 *y);

void func_08132208(Action *action)
{
    SceneObject *object;
    Unit *related;
    u8 x;
    u8 y;

    if (action->flags & 0x10)
        return;
    object = (SceneObject *)func_08099560(func_08096D7C(), (u32)action->target);
    related = object ? object->related : 0;
    if (func_08098E7C(func_08096D7C(), action->source, action->target, related, &x, &y)) {
        action->flags |= 8;
        action->result->x = x;
        action->result->y = y;
    }
}
