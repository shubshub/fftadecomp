#include "ffta.h"

// 0x080A05C4..0x080A0852: complete 654-byte target (327 instructions).

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_06[2];
} Position;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[0x10];
} Projection;

typedef struct {
    Projection vertical;
    Projection planar;
    s16 difference_x;
    s16 difference_y;
    s16 difference_z;
    s16 distance;
    Position start;
    Position end;
} PathState;

typedef struct {
    void *record;
    u8 unknown_04[4];
    s16 x;
    u8 unknown_0a[2];
    s16 z;
} SceneObject;

typedef struct {
    u8 unknown_00[0x80];
    void *list;
} SceneOwner;

extern void func_080A04E8(PathState *state, const Position *start,
                          const Position *end);
extern s32 func_080A7FE8(Projection *projection);
extern u8 func_0801CC18(u8 column, u8 row);
extern SceneObject *func_08099644(void *owner, s8 x, s8 z);
extern u8 func_0812E470(const void *unit);
extern u8 func_080C8298(const void *unit);
extern s32 func_08099C1C(SceneObject *object, s8 x, s8 z);

static inline void StepPath(PathState *state)
{
    if (state->distance >= state->difference_y) {
        func_080A7FE8(&state->planar);
        func_080A7FE8(&state->vertical);
    } else if (func_080A7FE8(&state->vertical)) {
        func_080A7FE8(&state->planar);
    }
    state->start.x = state->planar.x;
    state->start.z = state->planar.y;
    state->start.y = state->vertical.y;
}

SceneObject *func_080A05C4(SceneOwner *owner, const Position *start,
                           const Position *end, Position *out)
{
    PathState path;
    Position from;
    Position to;
    Position cell;
    Position current;
    Position target;
    Position previous;
    s32 height;
    s32 floor;
    SceneObject *object;
    s32 dx;
    s32 dz;
    /* A literal 12 is canonicalised to `dz <= 11` (cmp #11/ble); the ROM
       compares against 12 (cmp #12/blt), so the bound is a variable. */
    s32 range = 12;

    object = 0;
    floor = -1;
    height = 0;
    previous.z = -1;
    previous.y = -1;
    previous.x = -1;
    from.x = start->x >> 2;
    from.y = start->y >> 2;
    from.z = start->z >> 2;
    to.x = end->x >> 2;
    to.y = end->y >> 2;
    to.z = end->z >> 2;
    func_080A04E8(&path, &from, &to);
    target.x = path.end.x << 2;
    target.y = path.end.y << 2;
    target.z = path.end.z << 2;

    while (1) {
        current.x = path.start.x << 2;
        current.y = path.start.y << 2;
        current.z = path.start.z << 2;
        cell.x = current.x >> 5;
        cell.y = current.y >> 4;
        cell.z = current.z >> 5;
        if (cell.x != previous.x || cell.z != previous.z) {
            previous.x = cell.x;
            previous.z = cell.z;
            previous.y = func_0801CC18(previous.x, previous.z);
            floor = previous.y << 4;
            object = func_08099644(owner->list, previous.x, previous.z);
            if (object != 0
                && (!func_0812E470(object->record)
                    || func_080C8298(object->record)))
                object = 0;
            if (object == (SceneObject *)owner || object == 0)
                object = 0;
            else
                height = func_08099C1C(object, previous.x, previous.z) << 4;
        }
        if (object != 0 && height <= current.y && height + 0x30 > current.y) {
            dx = object->x - current.x;
            if (dx < 0)
                dx = -dx;
            dz = object->z - current.z;
            if (dz < 0)
                dz = -dz;
            if (dx >= dz)
                dz = dx;
            /* A literal `dz < 12` is folded to `<= 11` (cmp #11; ble); the ROM
             * compares against 12 (cmp #12; blt), so the bound was a named
             * value, not a literal.  080A0DEC has the same test. */
            if (dz < range)
                break;
        }
        if (floor > current.y)
            break;
        if (current.x == target.x && current.y == target.y
            && current.z == target.z)
            break;
        StepPath(&path);
    }
    *out = current;
    return object;
}
