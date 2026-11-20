#include "battle_position_search.h"

typedef struct {
    BattleUnit *owner;
    u8 unknown_04[0x324];
} GroupEntry;

typedef struct {
    GroupEntry entries[13];
    u16 count;
} Group;

typedef struct {
    void *unit;
    s8 x;
    s8 y;
    s8 end_x;
    s8 end_y;
    u16 first;
    u16 second;
} RangeRequest;

extern void *memcpy(void *destination, const void *source, unsigned long size);
extern s32 func_080BDF9C(PositionSearch *search);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern s32 func_080BE1F4(PositionSearch *search, s32 *work, Group *group,
                        s32 x, s32 y, u16 second, u8 side, Position *positions);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);
extern s32 func_080B4A1C(RangeRequest *request, u8 direction, u8 mode, u32 *output);
extern s32 func_080BE8E0(PositionSearch *search, s8 x, s8 y, s8 target_x,
                        s8 target_y, u8 *best_x, u8 *best_y, const void *positions,
                        s32 count, Position *tiles);
extern s32 func_080BE5F4(PositionSearch *search, u8 x, u8 y, s8 target_x,
                        s8 target_y, Position *positions);

/* Offsets within the public structure's unknown_18 byte array. */
enum {
    BEST_DISTANCE = 4,
    BEST_SCORE = 8,
    CURSOR_X = 12,
    CURSOR_Y = 13
};

static inline s32 read_best_distance(const PositionSearch *search)
{
    s32 value;
    memcpy(&value, search->unknown_18 + BEST_DISTANCE, sizeof(value));
    return value;
}

static inline void write_best_distance(PositionSearch *search, s32 value)
{
    memcpy(search->unknown_18 + BEST_DISTANCE, &value, sizeof(value));
}

static inline s32 read_best_score(const PositionSearch *search)
{
    s32 value;
    memcpy(&value, search->unknown_18 + BEST_SCORE, sizeof(value));
    return value;
}

static inline void write_best_score(PositionSearch *search, s32 value)
{
    memcpy(search->unknown_18 + BEST_SCORE, &value, sizeof(value));
}

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

static inline s32 score_position(PositionSearch *search, s8 x, s8 y,
                                 u8 *end_x, u8 *end_y, Position *positions)
{
    RangeRequest request;
    u16 entries[2];
    s32 count;

    func_0812F0D8(search->actor->unit, entries);
    request.unit = search->actor->unit;
    request.first = search->action;
    request.second = entries[0];
    request.x = x;
    request.y = y;
    request.end_x = x;
    request.end_y = y;
    count = func_080B4A1C(&request, 0, 0, (u32 *)positions);
    return func_080BE8E0(search, x, y, x, y, end_x, end_y, positions,
                         count, positions + count);
}

/* Self-targeted battle-position evaluator. A zero return finishes the search. */
u32 func_080BEAC8(PositionSearch *search, void *work)
{
    switch (search->status) {
    case 0:
    case 1:
        {
            Group *group;
            u16 entries[2];
            s32 i;

            if (!(u8)func_080BDF9C(search))
                return 0;
            group = search->status == 0 ? search->group : search->other_group;
            func_0812F0D8(search->actor->unit, entries);
            for (i = 0; i < group->count; i++) {
                BattleUnit *owner = group->entries[i].owner;
                if (owner != search->target)
                    func_080BE1F4(search, work, group, owner->unit->x, owner->unit->y,
                                  entries[0], search->status != 0, search->positions);
            }
            if (search->status == 1) {
                search->status = 2;
                write_best_distance(search, (-2147483647 - 1));
                write_best_score(search, -1);
            } else {
                search->status = 1;
            }
        }
        break;
    case 2:
        {
            s32 scanning = 1;
            do {
                s32 allow;
                if (search->flags & 4) {
                    PositionedUnit *unit = search->actor->unit;
                    allow = unit->x == search->unknown_18[CURSOR_X] &&
                            unit->y == search->unknown_18[CURSOR_Y];
                } else {
                    allow = 1;
                }
                if (tile_is_candidate(search->map, search->unknown_18[CURSOR_X],
                                      search->unknown_18[CURSOR_Y]) &&
                    allow && tile_is_open(search->map, search->unknown_18[CURSOR_X],
                                          search->unknown_18[CURSOR_Y])) {
                    s32 distance;
                    scanning = 0;
                    distance = func_080BE3B8(search, search->unknown_18[CURSOR_X],
                                             search->unknown_18[CURSOR_Y]);
                    if (read_best_distance(search) < distance) {
                        u8 end[2];
                        s32 score;
                        end[0] = search->unknown_18[CURSOR_X];
                        end[1] = search->unknown_18[CURSOR_Y];
                        score = score_position(search, search->unknown_18[CURSOR_X],
                                               search->unknown_18[CURSOR_Y], &end[0],
                                               &end[1], search->positions);
                        if (score > read_best_score(search)) {
                            search->has_position = 1;
                            search->start_x = search->unknown_18[CURSOR_X];
                            search->start_y = search->unknown_18[CURSOR_Y];
                            search->end_x = end[0];
                            search->end_y = end[1];
                            write_best_distance(search, distance);
                            write_best_score(search, score);
                        }
                    }
                }
                if (++search->unknown_18[CURSOR_X] > 15) {
                    search->unknown_18[CURSOR_X] = 0;
                    if (++search->unknown_18[CURSOR_Y] > 15) {
                        if (search->has_position == 1)
                            return 0;
                        search->status = 3;
                        search->unknown_18[CURSOR_X] = 0;
                        search->unknown_18[CURSOR_Y] = 0;
                        write_best_distance(search, (-2147483647 - 1));
                        return 1;
                    }
                }
            } while (scanning);
        }
        break;
    case 3:
        {
            u16 entries[2];
            s32 scanning;
            func_0812F0D8(search->actor->unit, entries);
            /* This pass retains its scan flag at 080BEF08. The grid-end branch returns directly. */
            scanning = 1;
            do {
                s32 allow;
                if (search->flags & 4) {
                    PositionedUnit *unit = search->actor->unit;
                    allow = unit->x == search->unknown_18[CURSOR_X] &&
                            unit->y == search->unknown_18[CURSOR_Y];
                } else {
                    allow = 1;
                }
                if (tile_is_candidate(search->map, search->unknown_18[CURSOR_X],
                                      search->unknown_18[CURSOR_Y]) &&
                    allow && tile_is_open(search->map, search->unknown_18[CURSOR_X],
                                          search->unknown_18[CURSOR_Y])) {
                    if (func_080BE5F4(search, search->unknown_18[CURSOR_X],
                                     search->unknown_18[CURSOR_Y], search->unknown_18[CURSOR_X],
                                     search->unknown_18[CURSOR_Y], search->positions) >= 0) {
                        s32 distance = func_080BE3B8(search, search->unknown_18[CURSOR_X],
                                             search->unknown_18[CURSOR_Y]);
                        if (read_best_distance(search) < distance) {
                            write_best_distance(search, distance);
                            search->has_position = 1;
                            search->start_x = search->unknown_18[CURSOR_X];
                            search->start_y = search->unknown_18[CURSOR_Y];
                            search->end_x = search->unknown_18[CURSOR_X];
                            search->end_y = search->unknown_18[CURSOR_Y];
                        }
                    }
                }
                if (++search->unknown_18[CURSOR_X] > 15) {
                    search->unknown_18[CURSOR_X] = 0;
                    if (++search->unknown_18[CURSOR_Y] > 15) {
                        search->status = 3;
                        search->unknown_18[CURSOR_X] = 0;
                        search->unknown_18[CURSOR_Y] = 0;
                        write_best_distance(search, 0);
                        return 0;
                    }
                }
            } while (scanning);
        }
    }
    return 1;
}
