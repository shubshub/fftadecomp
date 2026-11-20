#include "movement_tile.h"

typedef struct {
    u8 unknown_00[4];
    u8 kind;
} Unit;

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
} RenderScene;

typedef struct {
    Unit *unit;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_12[0x1E];
    u32 flags;
    u16 sprite_id;
    u16 animation;
    u8 unknown_38[0x1C];
    void *sprite;
    void *shadow;
    u8 unknown_5C[0x24];
    Scene *scene;
} RenderActor;

extern void func_0808EFCC(void *sprite, s16 x, s16 height, s16 y);
extern s32 func_0809D79C(s8 x, s8 y);
extern void (*data_08394040[])(void *, s32);

/* The same lookup is out of line at 0x08099644. */
static inline RenderActor *object_at(Scene *scene, s8 x, s8 y)
{
    TileSearch search;

    search.match = 0;
    search.x = x;
    search.y = y;
    func_080C7CC0(scene->objects, func_0809ABB0, &search);
    return (RenderActor *)search.match;
}

/* Actor and shadow positioning callback, 0x08097F04..0x0809801C (280 bytes). */
u32 func_08097F04(void *value, void *argument)
{
    RenderActor *actor = value;
    RenderScene *scene = argument;
    RenderActor *other;
    s32 height;
    u8 kind;
    u16 animation;

    if (actor->flags & 1)
        return 1;
    if ((actor->flags & 0x20000) && (scene->flags & 0x40))
        return 1;

    func_0808EFCC(actor->sprite, actor->x + actor->offset_x, actor->height,
                  actor->y + actor->offset_y);
    if (actor->flags & 0x8000)
        return 1;
    kind = actor->unit->kind;
    if (kind == 0x1F || kind == 0x40 || kind == 0x41 || kind == 0x42 ||
        kind == 0x43 || kind == 0x44 || kind == 0x45 || kind == 0x46)
        return 1;
    animation = actor->animation;
    if (animation == 0 || animation == 0xC || animation == 0x10 || animation == 0x80)
        return 1;

    height = func_0809D79C(actor->x >> 5, actor->y >> 5);
    other = object_at(actor->scene, actor->x >> 5, actor->y >> 5);
    if (other && other != actor && actor->height > other->height + 0x30)
        height = (other->height + 0x30) >> 4;

    if (!(actor->flags & 4)) {
        data_08394040[0](actor->shadow, -2);
        func_0808EFCC(actor->shadow, actor->x + actor->offset_x, height * 16,
                      actor->y + actor->offset_y);
    }
    return 1;
}
