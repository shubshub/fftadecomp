#include "ffta.h"

// Complete [0x080BE8E0, 0x080BE9EE): 270 bytes, 130 instructions.

typedef struct {
    void *unit;
} Owner080BE8E0;

typedef struct {
    Owner080BE8E0 *owner;
    u8 unknown_04[4];
    u16 identifier;
} Actor080BE8E0;

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
} Tile080BE8E0;

extern s32 func_080BE5F4(Actor080BE8E0 *actor, s8 x, s8 y, s8 target_x,
                         s8 target_y, Tile080BE8E0 *tiles);
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern int func_080B4A1C(RangeRequest *request, u8 direction, u8 mode,
                         Tile080BE8E0 *output);
extern s32 func_080B7EA0(const void *positions, s32 count, s8 x, s8 y);

s32 func_080BE8E0(Actor080BE8E0 *actor, s8 x, s8 y, s8 target_x, s8 target_y,
                  u8 *best_x, u8 *best_y, const void *positions, s32 count,
                  Tile080BE8E0 *tiles)
{
    RangeRequest request;
    u16 entries[2];
    s32 score;
    s32 best;
    s32 total;
    s32 pass;

    score = func_080BE5F4(actor, x, y, target_x, target_y, tiles);
    if (score < 0)
        return -1;

    func_0812F0D8(actor->owner->unit, entries);
    request.unit = actor->owner->unit;
    request.first = actor->identifier;
    request.second = entries[0];
    request.x = target_x;
    request.y = target_y;
    request.end_x = x;
    request.end_y = y;
    total = func_080B4A1C(&request, 0, 1, tiles);

    best = 0;
    /* The ROM runs the scan twice. */
    for (pass = 0; pass < 2; pass++) {
        s32 i;

        for (i = 0; i < total; i++) {
            score = func_080BE5F4(actor, tiles[i].x, tiles[i].y, target_x,
                                  target_y, tiles + total);
            if (score > 0 && best <= score
                && func_080B7EA0(positions, count, tiles[i].x, tiles[i].y)) {
                best = score;
                *best_x = tiles[i].x;
                *best_y = tiles[i].y;
            }
        }
    }
    return best;
}
