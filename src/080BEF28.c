#include "battle_position_search.h"

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
    s8 x;
    s8 y;
    u8 unknown_02[2];
    s32 score;
} RankedPosition;

/* This evaluator uses the shared state's 256-byte scratch allocation as
 * ranked positions. Its score and cursor occupy reserved common-state bytes. */
typedef union {
    PositionSearch common;
    struct {
        u8 unknown_00[0x1C];
        s32 best_score;
        u8 unknown_20[0x200 - 0x20];
        RankedPosition *tiles;
        Position *positions;
        s16 candidate_count;
        s16 candidate_index;
        s16 count;
        s16 first_position;
    } ranked;
} PositionSearchView;

#define RANKING(state) (((PositionSearchView *)(state))->ranked)

typedef struct {
    u16 id;
    u8 unknown_02[10];
    s16 value;
    u8 unknown_0E[3];
    u8 flags;
    u8 unknown_12[2];
} ActionRecord;

typedef struct {
    BattleUnit *owner;
    ActionRecord actions[40];
    u16 count;
    u8 unknown_326[2];
} GroupEntry;

typedef struct {
    GroupEntry entries[13];
    u16 count;
} Group;

extern s32 func_080BE7AC(PositionSearch *search, s8 x, s8 y, Position *tiles, RankedPosition *ranked);
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern s32 func_080B4A1C(RangeRequest *request, u8 direction, u8 mode, u32 *output);
extern s32 func_080B7EA0(const Position *positions, s32 count, s8 x, s8 y);
extern u32 func_080BE074(PositionSearch *search, s8 x, s8 y, s8 end_x, s8 end_y);
extern void func_080BDA30(Position *positions, s32 count, s8 x, s8 y);
extern s32 func_080BE3B8(PositionSearch *search, s8 x, s8 y);
extern u32 func_080CCD50(u16 action, u8 selector);

static inline GroupEntry *find_entry(Group *group, BattleUnit *actor)
{
    s32 i;

    for (i = 0; i < group->count; i++) {
        if (group->entries[i].owner == actor)
            return &group->entries[i];
    }
    return 0;
}

static inline ActionRecord *find_action(GroupEntry *entry, u16 action)
{
    s32 i;

    for (i = 0; i < entry->count; i++) {
        if (entry->actions[i].id == action)
            return &entry->actions[i];
    }
    return 0;
}

static inline u8 tile_is_marked(u8 *map, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 &&
        *(map + (y << 4) + x) != 0)
        return 1;
    return 0;
}

/* Complete Thumb symbol [0x080BEF28, 0x080BF5A2), 1,658 bytes including
 * literal pools. The dispatcher passes its work pointer in the second slot. */
u32 func_080BEF28(PositionSearch *search, void *work)
{
    switch (search->status) {
    case 0: {
        RangeRequest request;
        u16 entries[2];
        s32 count;

        RANKING(search).candidate_count = func_080BE7AC(search, search->target->unit->x,
            search->target->unit->y, search->positions, RANKING(search).tiles);
        if (!RANKING(search).candidate_count)
            return 0;
        if (RANKING(search).candidate_count < 0) {
            search->status = 3;
            break;
        }
        if (!func_0812F0D8(search->actor->unit, entries))
            entries[0] = 0;
        request.unit = search->actor->unit;
        request.first = search->action;
        request.second = entries[0];
        request.x = search->target->unit->x;
        request.y = search->target->unit->y;
        request.end_x = search->target->unit->x;
        request.end_y = search->target->unit->y;
        count = func_080B4A1C(&request, 0, 1, (u32 *)search->positions);
        RANKING(search).candidate_index = 0;
        if (!func_080B7EA0(search->positions, count, request.x, request.y))
            search->status = 2;
        else
            search->status = 1;
        break;
    }
    case 2: {
        s32 scanned = 0;

        while (RANKING(search).candidate_index < RANKING(search).candidate_count && scanned < 2) {
            s32 i = RANKING(search).candidate_index;
            if (func_080BE074(search, RANKING(search).tiles[i].x, RANKING(search).tiles[i].y,
                              RANKING(search).tiles[i].x, RANKING(search).tiles[i].y)) {
                search->start_x = RANKING(search).tiles[i].x;
                search->start_y = RANKING(search).tiles[i].y;
                search->end_x = RANKING(search).tiles[i].x;
                search->end_y = RANKING(search).tiles[i].y;
                search->has_position = 1;
                return 0;
            }
            scanned++;
            RANKING(search).candidate_index++;
        }
        if (RANKING(search).candidate_index >= RANKING(search).candidate_count)
            return 0;
        break;
    }
    case 1: {
        RangeRequest request;
        u16 entries[2];
        s32 score;
        s32 best_distance;
        s32 distance;
        s32 extra;
        s32 i;

        if (!func_0812F0D8(search->actor->unit, entries))
            entries[0] = 0;
        request.unit = search->actor->unit;
        request.first = search->action;
        request.second = entries[0];
        request.x = RANKING(search).tiles[RANKING(search).candidate_index].x;
        request.y = RANKING(search).tiles[RANKING(search).candidate_index].y;
        request.end_x = RANKING(search).tiles[RANKING(search).candidate_index].x;
        request.end_y = RANKING(search).tiles[RANKING(search).candidate_index].y;
        search->count = func_080B4A1C(&request, 0, 0, (u32 *)search->positions);
        func_080BDA30(search->positions, search->count, request.end_x, request.end_y);
        extra = func_080B4A1C(&request, 0, 1, (u32 *)(search->positions + search->count));
        best_distance = 0;
        RANKING(search).first_position = 0;
        RANKING(search).best_score = (-2147483647 - 1);
        for (i = RANKING(search).first_position; i < search->count; i++) {
            s32 dx;
            s32 dy;

            score = func_080BE3B8(search, search->positions[i].x, search->positions[i].y);
            dx = search->positions[i].x - RANKING(search).tiles[RANKING(search).candidate_index].x;
            if (dx < 0)
                dx = -dx;
            dy = search->positions[i].y - RANKING(search).tiles[RANKING(search).candidate_index].y;
            if (dy < 0)
                dy = -dy;
            distance = dx + dy;
            if (!search->side && distance <= best_distance)
                continue;
            if (RANKING(search).best_score >= score)
                continue;
            if (!tile_is_marked(search->map, search->positions[i].x, search->positions[i].y))
                continue;
            if (func_080B7EA0(search->positions + search->count, extra,
                              search->positions[i].x, search->positions[i].y)) {
                ActionRecord *action = 0;
                GroupEntry *entry = find_entry(search->group, search->actor);
                if (entry) {
                    action = find_action(entry, search->action);
                } else {
                    entry = find_entry(search->other_group, search->actor);
                    if (entry)
                        action = find_action(entry, search->action);
                }
                /* The group lookup must supply an action on this path. The
                 * original reads its flags before the pointer check below. */
                if (action->flags & 1)
                    continue;
                if (action && action->value > 0)
                    continue;
                if (!func_080CCD50(search->action, 11))
                    continue;
            }
            if (!func_080BE074(search, search->positions[i].x, search->positions[i].y,
                               RANKING(search).tiles[RANKING(search).candidate_index].x,
                               RANKING(search).tiles[RANKING(search).candidate_index].y))
                continue;
            best_distance = distance;
            RANKING(search).best_score = score;
            search->start_x = search->positions[i].x;
            search->start_y = search->positions[i].y;
            search->end_x = RANKING(search).tiles[RANKING(search).candidate_index].x;
            search->end_y = RANKING(search).tiles[RANKING(search).candidate_index].y;
            search->has_position = 1;
        }
        if (search->has_position)
            return 0;
        if (++RANKING(search).candidate_index >= RANKING(search).candidate_count)
            return 0;
        break;
    }
    case 3: {
        Group *group = search->group;
        s32 i;
        s32 j;
        s32 best_score;
        s8 x;
        s8 y;

        for (i = 0; i < group->count; i++) {
            for (j = 0; j < group->entries[i].count; j++) {
                if (group->entries[i].actions[j].id == search->action &&
                    (group->entries[i].actions[j].flags & 2))
                    return 0;
            }
        }
        best_score = (-2147483647 - 1);
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                if (func_080BE074(search, x, y, x, y)) {
                    s32 score = func_080BE3B8(search, x, y);
                    if (score > best_score) {
                        best_score = score;
                        search->start_x = x;
                        search->start_y = y;
                        search->end_x = x;
                        search->end_y = y;
                        search->has_position = 1;
                    }
                }
            }
        }
        return 0;
    }
    }
    return 1;
}
