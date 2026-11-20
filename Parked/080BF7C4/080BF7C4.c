#include "battle_position_search.h"

typedef struct {
    void *unit;
    s8 x, y, end_x, end_y;
    u16 first, second;
} RangeRequest;

typedef struct {
    s16 x, y, z;
    u8 unknown_06[2];
} HitPosition;

typedef struct {
    u16 status;
    u16 depth;
    u16 stack[(0x200 - 0x1BC) / 2];
} SearchPhase;

typedef union {
    PositionSearch common;
    struct {
        u8 unknown_00[0x1C];
        s32 best_score;
        u8 unknown_20[6];
        u8 range;
        u8 weapon_19;
        u8 unknown_28[4];
        u8 selection[0x1AC - 0x2C];
        u8 unknown_1AC[0x1B8 - 0x1AC];
        SearchPhase phase;
        u8 unknown_200[0xE];
        s16 index;
    } weapon;
} WeaponSearch;

#define WEAPON(state) (((WeaponSearch *)(state))->weapon)
#define PHASE(state) (WEAPON(state).phase)
#define CURRENT(state) ((state)->positions[WEAPON(state).index])

extern s32 func_080BDF9C(PositionSearch *search);
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern u8 func_0812EED0(void *unit, u16 item);
extern u8 func_0812EE98(void *unit, u16 item);
extern s32 func_080B4A1C(RangeRequest *request, u8 direction, u8 mode, u32 *output);
extern void func_080BDA30(Position *positions, s32 count, s8 x, s8 y);
extern void func_080A84E8(void *selection, BattleUnit *actor, BattleUnit *target,
                          s8 x, s8 y, s8 range, u32 flags);
extern u32 func_080A11DC(void *selection, u32 budget);
extern u32 func_080A86EC(const void *selection);
extern BattleUnit *func_080A8700(void *actor, BattleUnit *target, s8 x, s8 y,
                                 HitPosition *hit);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);

static inline u8 *tile_at(u8 *map, s8 x, s8 y)
{
    return map + (y << 4) + x;
}

static inline u8 tile_is_marked(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 && *tile_at(map, x, y) != 0)
        return 1;
    return 0;
}

static inline u8 tile_is_open(u8 *map, s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 || (*tile_at(map, x, y) & 0x80))
        return 0;
    return 1;
}

static inline u8 tile_is_candidate(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 && (*tile_at(map, x, y) & ~0x80) == 2)
        return 1;
    return 0;
}

static inline s32 magnitude(s32 difference)
{
    if (difference < 0)
        difference = -difference;
    return difference;
}

static inline s32 saved_distance(PositionSearch *search)
{
    s32 distance = 0;
    if (search->has_position)
        distance = magnitude(search->start_x - search->target->unit->x)
             + magnitude(search->start_y - search->target->unit->y);
    return distance;
}

static inline s32 current_distance(PositionSearch *search)
{
    return magnitude(search->target->unit->x - CURRENT(search).x)
         + magnitude(search->target->unit->y - CURRENT(search).y);
}

/* Position evaluator for equipped weapon kinds 13, 14 and 19. */
u32 func_080BF7C4(PositionSearch *search, void *work)
{
    u16 entries[2];
    RangeRequest request;
    HitPosition hit;
    s32 distance;
    s32 previous;
    s8 scanned;
    SearchPhase *phase;

    switch (PHASE(search).status) {
    case 0:
        if (!(u8)func_080BDF9C(search))
            return 0;
        func_0812F0D8(search->actor->unit, entries);
        WEAPON(search).range = func_0812EED0(search->actor->unit, entries[0]);
        if (func_0812EE98(search->actor->unit, entries[0]) == 19)
            WEAPON(search).weapon_19 = 1;
        else
            WEAPON(search).weapon_19 = 0;
        request.unit = search->actor->unit;
        request.first = search->action;
        request.second = entries[0];
        request.x = search->target->unit->x;
        request.y = search->target->unit->y;
        request.end_x = request.x;
        request.end_y = request.y;
        search->count = func_080B4A1C(&request, 0, 0, (u32 *)search->positions);
        if (search->count <= 0)
            return 0;
        func_080BDA30(search->positions, search->count, request.end_x, request.end_y);
        WEAPON(search).index = 0;
        WEAPON(search).best_score = (-2147483647 - 1);
        PHASE(search).status = 1;
        /* fall through */
    case 1:
        for (scanned = 0; WEAPON(search).index < search->count && scanned < 12;
             ++WEAPON(search).index, ++scanned) {
            u8 allowed = 1;
            if (search->flags & 4) {
                if (search->actor->unit->x != CURRENT(search).x &&
                    search->actor->unit->y != CURRENT(search).y)
                    allowed = 0;
            }
            if (!allowed ||
                !tile_is_marked(search->map, CURRENT(search).x, CURRENT(search).y) ||
                !tile_is_open(search->map, CURRENT(search).x, CURRENT(search).y))
                continue;

            distance = current_distance(search);
            previous = 0;
            if (search->has_candidate)
                previous = magnitude(search->candidate_x - search->target->unit->x)
                         + magnitude(search->candidate_y - search->target->unit->y);
            if (previous < distance) {
                search->has_candidate = 1;
                search->candidate_x = CURRENT(search).x;
                search->candidate_y = CURRENT(search).y;
                search->candidate_end_x = search->target->unit->x;
                search->candidate_end_y = search->target->unit->y;
            }
            if (!tile_is_candidate(search->map, CURRENT(search).x, CURRENT(search).y))
                continue;
            if (saved_distance(search) >= distance)
                continue;
            if (WEAPON(search).weapon_19) {
                phase = &PHASE(search);
                phase->stack[phase->depth++] = phase->status;
                phase->status = 3;
                goto running;
            }
            func_080A84E8(WEAPON(search).selection, search->actor, search->target,
                          CURRENT(search).x, CURRENT(search).y, WEAPON(search).range, 0);
            phase = &PHASE(search);
            phase->stack[phase->depth++] = phase->status;
            phase->status = 2;
            goto running;
        }
        if (WEAPON(search).index >= search->count)
            return 0;
        break;
    case 2:
        while (func_080A11DC(WEAPON(search).selection, 8)) {}
        if (func_080A86EC(WEAPON(search).selection) == (u32)search->target)
            PHASE(search).status = 4;
        else {
            ++WEAPON(search).index;
            phase = &PHASE(search);
            phase->status = phase->stack[--phase->depth];
        }
        break;
    case 3:
        if (func_080A8700(search->actor, search->target, CURRENT(search).x,
                         CURRENT(search).y, &hit) == search->target)
            PHASE(search).status = 4;
        else {
            ++WEAPON(search).index;
            phase = &PHASE(search);
            phase->status = phase->stack[--phase->depth];
        }
        break;
    case 4:
        previous = saved_distance(search);
        distance = current_distance(search);
        if (previous == distance && previous != 0) {
            s32 score = func_080BE3B8(search, search->start_x, search->start_y);
            if (score > func_080BE3B8(search, CURRENT(search).x, CURRENT(search).y)) {
                ++WEAPON(search).index;
                phase = &PHASE(search);
                phase->status = phase->stack[--phase->depth];
                break;
            }
        }
        if (previous < distance) {
            search->start_x = CURRENT(search).x;
            search->start_y = CURRENT(search).y;
            search->end_x = search->target->unit->x;
            search->end_y = search->target->unit->y;
            search->has_position = 1;
        }
        ++WEAPON(search).index;
        phase = &PHASE(search);
        phase->status = phase->stack[--phase->depth];
        break;
    }
running:
    return 1;
}
