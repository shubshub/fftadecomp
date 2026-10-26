#include "ffta.h"

/* 0x080BF5A4..0x080BF7C2: 542 bytes, 257 instructions, including pools. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} PositionedUnit;

typedef struct {
    PositionedUnit *unit;
} UnitReference;

typedef struct {
    UnitReference *actor;
    UnitReference *target;
    u16 unknown_08;
    u16 unit_value;
    u8 unknown_0C[0x1A0];
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    u8 unknown_1B0;
    u8 has_position;
    u8 unknown_1B2[6];
    u16 status;
    u8 unknown_1BA[0x5A];
    u8 *map;
    u8 flags;
} PositionSearch;

extern u16 func_080C13C8(PositionedUnit *unit);
extern u32 func_080BE074(PositionSearch *search, s8 x1, s8 y1, s8 x2, s8 y2);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);

static inline u8 tile_is_open(u8 *map, s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 || (*(map + y * 16 + x) & 0x80)) {
        return 0;
    }
    return 1;
}

static inline u8 tile_is_candidate(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 &&
        (*(map + y * 16 + x) & ~0x80) == 2) {
        return 1;
    }
    return 0;
}

u32 func_080BF5A4(PositionSearch *search)
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
