#include "ffta.h"

// Complete [0x08097814, 0x08097A02): 494 bytes.

typedef struct ListContext08097814 ListContext08097814;
typedef struct ListNode08097814 ListNode08097814;

typedef struct {
    u8 unknown_00[0xFC];
    u8 state;
    u8 mode;
} Object08097814;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08097814 *list;
} Owner08097814;

typedef struct {
    Object08097814 *object;
    u8 unknown_04[0x18];
    u8 flags;
    u8 unknown_1D[0x63];
    Owner08097814 *owner;
} Unit08097814;

typedef struct {
    void *context;
    Unit08097814 *unit;
} Pair08097814;

typedef s32 (*PairCallback08097814)(Unit08097814 *node, Pair08097814 *pair);

typedef struct {
    Pair08097814 *argument;
    PairCallback08097814 callback;
} Closure08097814;

extern u8 func_080C8298(const Object08097814 *object);
extern u8 func_080C8240(Object08097814 *object);
extern void func_080C7CC0(ListContext08097814 *context,
                          u32 (*callback)(ListNode08097814 *, void *),
                          Closure08097814 *closure);
extern u32 func_0809ABE8(ListNode08097814 *node, void *closure);
extern s32 func_0809779C(Unit08097814 *node, Pair08097814 *pair);
extern u8 func_0801CC7C(u8 x, u8 y);
extern u8 func_0801CC18(u8 x, u8 y);
extern u8 func_0801CD08(u8 x, u8 y);
extern void func_081491C0(void *, s16, s16, u32, u32, u32, u32, u32);

static inline void visit_units(Unit08097814 *unit, Pair08097814 *pair)
{
    Owner08097814 *owner = unit->owner;
    Closure08097814 closure;
    PairCallback08097814 callback = func_0809779C;

    closure.argument = pair;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
}

void func_08097814(void *context, u16 x, u16 y, void *argument)
{
    Unit08097814 *unit = argument;
    u8 column;
    u8 row;
    u8 height;
    u8 terrain;

    if ((s16)x < 0 || (s16)y < 0) {
        Pair08097814 pair;

        pair.unit = unit;
        pair.context = context;
        if (func_080C8298(unit->object)) {
            visit_units(unit, &pair);
        } else {
            Object08097814 *object = unit->object;

            if (object->state == 2)
                return;
            if (object->state == 3)
                return;
            if (unit->flags & 0x40)
                return;
            if (func_080C8240(object))
                visit_units(unit, &pair);
            else
                visit_units(unit, &pair);
        }
        return;
    }

    column = x;
    row = y;
    if (func_0801CC7C(column, row) == 0) {
        if (unit->object->state == 3)
            func_081491C0(context, x, y, 1, 0, 1, 0, 0);
        else
            func_081491C0(context, x, y, 0, 0, 1, 0, 0);
        return;
    }

    height = func_0801CC18(column, row);
    terrain = func_0801CD08(column, row);
    if (((terrain & 1) && (u8)(unit->object->state - 2) > 1) || (u8)(terrain & 8)) {
        func_081491C0(context, x, y, 0, 0, 1, 0, 0);
        return;
    }
    if (terrain & 2) {
        switch (unit->object->mode) {
        case 2:
            func_081491C0(context, x, y, 1, height - 1, 0, 0, 0);
            return;
        case 3:
        case 4:
            break;
        default:
            func_081491C0(context, x, y, 1, height, 1, 0, 0);
            return;
        }
    }
    if ((terrain & 4) && unit->object->mode != 4)
        func_081491C0(context, x, y, 1, height, 1, 0, 0);
    else
        func_081491C0(context, x, y, 1, height, 0, 0, 0);
}
