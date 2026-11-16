#include "ffta.h"

/* Complete target [0x080BE074, 0x080BE1F4): 384 bytes, 185 instructions.
 * f0 b5 4f 46 46 46 c0 b4 05 1c 07 98 09 06 12 06
 * 1b 06 1b 0e 98 46 00 06 00 0e 81 46 0e 0e 17 0e
 * 12 16 85 23 9b 00 e8 18 03 68 09 16 00 29 0e db
 * 10 1c 00 28 0b db 0f 29 09 dc 0f 28 07 dc 00 01
 * 18 18 40 18 01 78 80 20 08 40 00 28 01 d0 00 20
 * 00 e0 01 20 00 28 00 d1 86 e0 86 21 89 00 68 18
 * 01 78 04 20 08 40 00 28 10 d0 28 68 02 68 10 1c
 * f6 30 01 78 30 06 00 16 81 42 75 d1 10 1c f7 30
 * 01 78 38 06 00 16 81 42 6e d1 1f e0 30 06 3a 06
 * 14 16 85 23 9b 00 e9 18 09 68 03 16 84 46 00 2b
 * 11 db 20 1c 00 28 0e db 0f 2b 0c dc 0f 28 0a dc
 * 00 01 08 18 c0 18 00 78 81 21 49 42 08 40 02 28
 * 01 d1 01 20 00 e0 00 20 00 28 01 d0 01 20 4c e0
 * 13 16 85 21 89 00 68 18 04 68 60 46 01 16 00 29
 * 0e db 18 1c 00 28 0b db 0f 29 09 dc 0f 28 07 dc
 * 00 01 20 18 40 18 00 78 00 28 01 d0 01 20 00 e0
 * 00 20 00 28 30 d0 d9 21 49 00 68 18 00 78 00 28
 * 16 d0 28 68 c0 6b 63 46 19 0e 12 0e 8b f0 0c f9
 * 04 1c 28 68 c0 6b 14 4a a9 18 09 78 da 23 5b 00
 * ea 18 12 78 8b f0 00 f9 24 06 00 06 84 42 13 d2
 * d9 20 40 00 29 18 01 20 08 70 0b 49 68 18 06 70
 * da 22 52 00 a8 18 07 70 08 4b e8 18 41 46 01 70
 * 02 32 a8 18 4b 46 03 70 00 20 18 bc 98 46 a1 46
 * f0 bc 02 bc 08 47 00 00 b3 01 00 00 b5 01 00 00 */

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} PositionedUnit;

typedef struct {
    PositionedUnit *unit;
    u8 unknown_04[0x38];
    void *map;
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
    u8 has_candidate;
    u8 candidate_x;
    u8 candidate_y;
    u8 candidate_end_x;
    u8 candidate_end_y;
    u8 unknown_1B7;
    u16 status;
    u8 unknown_1BA[0x5A];
    u8 *map;
    u8 flags;
} PositionSearch;

extern u8 func_081493AC(void *map, u8 x, u8 y);

/* tile_at, tile_is_open and tile_is_candidate are the helpers of
 * src/080BF5A4.c, character for character. */
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

/* In bounds and nonzero.  The ROM builds this 0/1 result and tests it again
 * (0x080BE170..0x080BE178), as at the two shared predicates (0x080BE0C2,
 * 0x080BE136), and re-checks the bounds the first predicate already passed. */
static inline u8 tile_is_marked(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 && *tile_at(map, x, y) != 0) {
        return 1;
    }
    return 0;
}

u32 func_080BE074(PositionSearch *search, s8 x, s8 y, s8 end_x, s8 end_y)
{
    if (!tile_is_open(search->map, x, y))
        return 0;
    if (search->flags & 4) {
        if (search->actor->unit->x != x || search->actor->unit->y != y)
            return 0;
        return 1;
    }
    if (tile_is_candidate(search->map, x, y))
        return 1;
    if (tile_is_marked(search->map, x, y)) {
        if (search->has_candidate &&
            func_081493AC(search->actor->map, x, y) >=
                func_081493AC(search->actor->map, search->candidate_x,
                              search->candidate_y))
            return 0;
        search->has_candidate = 1;
        search->candidate_x = x;
        search->candidate_y = y;
        search->candidate_end_x = end_x;
        search->candidate_end_y = end_y;
    }
    return 0;
}
