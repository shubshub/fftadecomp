#include "ffta.h"

/* 0x080D8B7C..0x080D8BD8: 92 bytes. */
typedef struct {
    u8 unknown_00[10];
    s8 x;
    s8 y;
} ActorTilePosition;

extern ActorTilePosition *func_080A880C(u32 actor_id);
extern u8 func_0801CC18(u8 x, u8 y);
extern void func_0801CA78(s16 x, u8 height, s16 y,
                         u32 first, u32 second, u32 third);

static inline void get_actor_coordinates(u32 actor_id, s16 *x, s16 *y)
{
    ActorTilePosition *actor = func_080A880C(actor_id);

    *x = actor->x;
    *y = actor->y;
}

void func_080D8B7C(u32 actor_id, u32 first, u32 second, u32 third)
{
    s16 x, y;
    u8 height;

    get_actor_coordinates(actor_id, &x, &y);
    height = func_0801CC18(x, y);
    func_0801CA78(x, height, y,
                  first, second, third);
}
