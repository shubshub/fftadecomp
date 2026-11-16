#include "ffta.h"

/* Complete [0x080BFDB0, 0x080C01CE): 1054 bytes, including literal pools. */

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} PositionedUnit;

typedef struct {
    PositionedUnit *unit;
} UnitReference;

typedef struct {
    void *unit;
    s8 x;
    s8 y;
    s8 end_x;
    s8 end_y;
    u16 first;
    u16 second;
} RangeRequest;

typedef struct {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown_03;
} Position;

typedef struct {
    UnitReference *actor;
    UnitReference *target;
    u16 action;
    u16 unit_value;
    u8 unknown_0C[0x1A0];
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    u8 direction;
    u8 has_position;
    u8 has_candidate;
    u8 candidate_x;
    u8 candidate_y;
    u8 candidate_end_x;
    u8 candidate_end_y;
    u8 unknown_1B7;
    u16 status;
    u8 unknown_1BA[0x4A];
    Position *positions;
    u8 unknown_208[4];
    s16 count;
    u8 unknown_20E[6];
    u8 *map;
    u8 flags;
} PositionSearch;

extern const s8 data_08394658[];
extern u8 func_080BDF9C(PositionSearch *search);
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern u8 func_080C48A4(PositionedUnit *first, PositionedUnit *second, u16 action);
extern u32 func_080CCD50(u16 action, u8 selector);
extern s32 func_080B4A1C(RangeRequest *request, s8 direction, u8 mode,
                         Position *output);
extern s32 func_080B7EA0(const Position *positions, s32 count, s8 x, s8 y);
extern s32 func_080BE494(PositionSearch *search, const Position *positions,
                         s32 count);
extern u32 func_080BE074(PositionSearch *search, s8 x1, s8 y1, s8 x2, s8 y2);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);

/* tile_at, tile_is_open and tile_is_candidate are the helpers of
 * src/080BF5A4.c, character for character; inlined at 0x080BFF5E-0x080BFF9C
 * and 0x080C00CA-0x080C0106. */
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

u32 func_080BFDB0(PositionSearch *search)
{
    u16 entries[2];
    RangeRequest request;
    s32 direction;
    u32 i;
    s32 j;
    s32 best_score;
    s32 best_distance;
    s32 fallback_score;
    s32 fallback_distance;
    u8 facing;
    Position *candidates;

    if (search->status == 0) {
        if (!func_080BDF9C(search))
            return 0;
        if (!func_0812F0D8(search->actor->unit, entries))
            entries[0] = 0;
        if (!func_080C48A4(search->actor->unit, search->target->unit, search->action))
            return 0;

        facing = search->actor->unit->direction;
        best_score = -1;
        best_distance = -2147483647 - 1;
        fallback_score = -1;
        fallback_distance = -2147483647 - 1;

        for (i = 0; i < 4; i++) {
            s32 back;

            direction = search->target->unit->direction + data_08394658[i];
            if (direction < 0)
                direction += 4;
            if (direction > 3)
                direction -= 4;
            back = direction - 2;
            if (back < 0)
                back += 4;
            if (back > 3)
                back -= 4;

            request.unit = search->actor->unit;
            if (func_080CCD50(search->action, 4) & 0x80)
                request.first = 0;
            else
                request.first = search->action;
            request.second = entries[0];
            request.x = search->target->unit->x;
            request.y = search->target->unit->y;
            request.end_x = request.x;
            request.end_y = request.y;
            search->count = func_080B4A1C(&request, back, 1, search->positions);
            if (search->count == 0)
                continue;

            candidates = &search->positions[search->count];
            for (j = 0; j < search->count; j++) {
                s32 count;
                s32 score;
                s32 distance;
                Position *path;

                request.unit = search->actor->unit;
                request.first = search->action;
                request.second = entries[0];
                request.x = search->positions[j].x;
                request.y = search->positions[j].y;
                request.end_x = search->target->unit->x;
                request.end_y = search->target->unit->y;
                count = func_080B4A1C(&request, direction, 1, candidates);
                path = &candidates[count];
                if (!func_080B7EA0(candidates, count, search->target->unit->x,
                                   search->target->unit->y))
                    continue;
                if (!tile_is_open(search->map, request.x, request.y))
                    continue;
                if ((search->flags & 4) &&
                    (request.x != search->actor->unit->x ||
                     request.y != search->actor->unit->y))
                    continue;
                score = func_080BE494(search, candidates, count);
                if (score <= 0)
                    continue;

                request.unit = search->actor->unit;
                request.first = search->action;
                request.second = entries[0];
                request.x = search->positions[j].x;
                request.y = search->positions[j].y;
                request.end_x = search->target->unit->x;
                request.end_y = search->target->unit->y;
                if (!func_080B7EA0(path, func_080B4A1C(&request, direction, 0, path),
                                   search->target->unit->x,
                                   search->target->unit->y))
                    continue;
                distance = func_080BE3B8(search, request.x, request.y);

                if (score >= fallback_score) {
                    /* The ROM keeps this test as a value: movs r0, #1 at 0x080C0066,
                     * movs r0, #0 at 0x080C0072, cmp r0, #0 at 0x080C0074. */
                    u8 better = 1;

                    if (score == fallback_score && distance <= fallback_distance)
                        better = 0;

                    if (better) {
                        u8 saved = search->has_candidate;

                        search->has_candidate = 0;
                        if (!func_080BE074(search, request.x, request.y,
                                           search->target->unit->x,
                                           search->target->unit->y)) {
                            if (!search->has_candidate) {
                                search->has_candidate = saved;
                                continue;
                            }
                            fallback_score = score;
                            fallback_distance = distance;
                            continue;
                        }
                    }
                    fallback_score = score;
                    fallback_distance = distance;
                }

                if (!tile_is_candidate(search->map, request.x, request.y))
                    continue;
                if (score < best_score)
                    continue;
                if (score == best_score && distance < best_distance)
                    continue;
                best_distance = distance;
                best_score = score;
                search->start_x = request.x;
                search->start_y = request.y;
                search->direction = direction;
                search->end_x = search->target->unit->x;
                search->end_y = search->target->unit->y;
                search->has_position = 1;
            }
            if ((search->flags & 1) && search->has_position)
                break;
        }

        search->actor->unit->direction = facing;
        return 0;
    }
    return 1;
}
