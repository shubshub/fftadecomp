#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
    u8 unknown_0E[0x22];
    u32 flags;
} BattleActor;

typedef struct {
    BattleActor *source;
    BattleActor *target;
    BattleActor **matches;
    u8 count;
    u8 check_chance;
} Search;

extern u8 func_0812E4A8(const void *unit);
extern u8 func_080C8384(const void *unit);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern s32 func_0812E1A8(void *unit, u8 from_x, u8 from_y, u8 to_x, u8 to_y,
                         u16 item, u8 flags);
extern s32 func_0812E130(const void *unit, const void *other, u32 options);
extern u8 func_0812F1DC(u16 chance);

s32 func_080A95EC(BattleActor *actor, Search *search)
{
    u16 entries[2];

    if (actor == search->source || actor == search->target)
        return 1;
    if (!func_0812E4A8(actor->unit) || func_080C8384(actor->unit))
        return 1;
    if (actor->flags & 0x8000)
        return 1;
    if (func_0812F0D8(actor->unit, entries) <= 0)
        entries[0] = 0;
    if (!func_0812E1A8(actor->unit, actor->x >> 5, actor->y >> 5,
                       search->target->x >> 5, search->target->y >> 5,
                       entries[0], 8))
        return 1;
    if (search->check_chance == 1 &&
        !func_0812F1DC(func_0812E130(actor->unit, search->target->unit, 0) + 10))
        return 1;
    search->matches[search->count] = actor;
    search->count++;
    return 1;
}
