#include "battle_position_search.h"

/* 0x080BF5A4..0x080BF7C2: 542 bytes, 257 instructions, including pools. */
extern u16 func_080C13C8(PositionedUnit *unit);
extern u32 func_080BE074(PositionSearch *search, s8 x1, s8 y1, s8 x2, s8 y2);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);

static inline u8 *tile_at(u8 *map, s8 x, s8 y)
{
    return map + (y << 4) + x;
}

static inline u8 tile_is_open(u8 *map, s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 || (*tile_at(map, x, y) & 0x80)) {
        return 0;
    }
    return 1;
}

static inline u8 tile_is_candidate(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 &&
        (*tile_at(map, x, y) & ~0x80) == 2) {
        return 1;
    }
    return 0;
}

u32 func_080BF5A4(PositionSearch *search, void *work)
{
    if (search->status == 0) {
        if (search->actor == search->target) {
            search->unit_value = func_080C13C8(search->actor->unit);
            if (tile_is_open(search->map, search->actor->unit->x, search->actor->unit->y)) {
                search->start_x = search->actor->unit->x;
                search->start_y = search->actor->unit->y;
                search->end_x = search->actor->unit->x;
                search->end_y = search->actor->unit->y;
                search->has_position = 1;
                return 0;
            } else {
                s32 best = (-2147483647 - 1);
                s8 x;
                s8 y;

                for (y = 0; y < 16; y++) {
                    for (x = 0; x < 16; x++) {
                        s32 score;
                        if (!tile_is_candidate(search->map, x, y)) {
                            continue;
                        }
                        if ((search->flags & 4) &&
                            (search->actor->unit->x != x || search->actor->unit->y != y)) {
                            continue;
                        }
                        if (!tile_is_open(search->map, x, y)) {
                            continue;
                        }
                        if (!func_080BE074(search, x, y, x, y)) {
                            continue;
                        }
                        score = func_080BE3B8(search, x, y);
                        if (best < score) {
                            best = score;
                            search->start_x = x;
                            search->start_y = y;
                            search->end_x = x;
                            search->end_y = y;
                            search->has_position = 1;
                        }
                    }
                }
            }
        }
    return 0;
    }
    return 1;
}
