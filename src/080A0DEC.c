#include "ffta.h"

// Complete [0x080A0DEC, 0x080A0FF0): 516 bytes, 242 instructions.

typedef struct {
    s16 x;
    s16 height;
    s16 y;
    s16 unknown_06;
} Position080A0DEC;

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit080A0DEC;

typedef struct Actor080A0DEC Actor080A0DEC;
struct Actor080A0DEC {
    Unit080A0DEC *unit;
    u8 unknown_04[0x7C];
    void *field;
};

typedef struct {
    u8 unknown_00[0x4C];
    s16 step;
} Path080A0DEC;

extern s32 func_080A0D04(Path080A0DEC *path, void *arg, s32 step,
                         Position080A0DEC *out);
extern u8 func_0801CC18(u8 x, u8 y);
extern Actor080A0DEC *func_08099644(void *field, s8 x, s8 y);
extern u8 func_0812E470(Unit080A0DEC *unit);
extern u8 func_080C8298(Unit080A0DEC *unit);
extern s32 func_08099C1C(Actor080A0DEC *actor, s8 x, s8 y);

s32 func_080A0DEC(Path080A0DEC *path, Actor080A0DEC *self, void *arg,
                  s32 count, Actor080A0DEC **hit, Position080A0DEC *out,
                  s32 ignore_actors)
{
    s32 i;
    s32 more;
    Position080A0DEC pos;
    Position080A0DEC tile;
    Position080A0DEC last;
    Position080A0DEC target;
    Actor080A0DEC *actor;
    s16 floor;
    s32 dx;
    s32 dy;
    s32 range;

    last.y = -1;
    last.height = -1;
    last.x = -1;
    actor = 0;
    floor = 0;
    /* A literal 12 is canonicalised to `dy <= 11` (cmp #11/ble); the ROM
       compares against 12 (cmp #12/blt), so the bound is a variable. */
    range = 12;

    for (i = 0; ; i++, path->step++) {
        if (i >= count)
            return -1;
        more = func_080A0D04(path, arg, path->step, &pos);
        tile.x = pos.x >> 5;
        tile.height = pos.height >> 4;
        tile.y = pos.y >> 5;
        if (tile.x != last.x || tile.y != last.y) {
            last = tile;
            last.height = func_0801CC18(last.x, last.y);
            floor = last.height << 4;
            actor = func_08099644(self->field, last.x, last.y);
            if (actor != 0 && (!func_0812E470(actor->unit)
                               || func_080C8298(actor->unit)))
                actor = 0;
            if (actor == self || actor == 0) {
                actor = 0;
            } else {
                target.x = (actor->unit->x << 5) + 16;
                target.y = (actor->unit->y << 5) + 16;
                target.height = func_08099C1C(actor, last.x, last.y) << 4;
            }
        }
        if (!ignore_actors) {
            if (actor != 0 && target.height <= pos.height
                && target.height + 0x30 > pos.height) {
                dx = target.x - pos.x;
                if (dx < 0)
                    dx = -dx;
                dy = target.y - pos.y;
                if (dy < 0)
                    dy = -dy;
                if (dx >= dy)
                    dy = dx;
                if (dy < range) {
                    *hit = actor;
                    break;
                }
            }
            if (pos.height <= floor)
                break;
        }
        if (!more)
            break;
    }
    *out = pos;
    return path->step + 1;
}
