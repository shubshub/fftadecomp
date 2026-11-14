#include "ffta.h"

// Complete target: [0x080B55CC, 0x080B587E), 690 bytes, 322 instructions.
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
    u8 direction;
} BattleUnit;

typedef struct {
    BattleUnit *unit;
    u8 unknown_04[4];
    u16 x;
    u8 unknown_0a[2];
    u16 y;
    u8 unknown_0e[0x11];
    u8 direction;
} BattleActor;

typedef struct {
    u16 x;
    s16 direction;
    u16 y;
} SavedPosition;

extern void *func_0802D72C(u8 first);
extern void func_0802B8CC(void *task, u8 mode, s16 value);
extern s32 func_0809D6BC(s8 dx, s8 dy);
extern void func_0809920C(BattleActor *actor, u8 selection);
extern void func_0809915C(BattleActor *actor, u8 selection);
extern u16 func_0812E6A4(const BattleUnit *unit);
extern u8 func_080C8240(const BattleUnit *unit);
extern s32 func_08130200(BattleUnit *source, BattleUnit *target, u16 action,
                         u16 equipment, u16 attribute, u16 mode);
extern u8 func_0812F0E4(const BattleUnit *unit, s8 column, s8 row);
extern u32 func_080CCD50(u16 identifier, u8 field);
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern s32 func_0812E1A8(const BattleUnit *unit, u8 x, u8 y, u8 other_x,
                         u8 other_y, u16 entry, u8 mode);
extern s32 func_0812EF94(BattleUnit *source, BattleUnit *target, u16 entry,
                         u8 mode, u8 option);
extern s32 func_0812E0BC(BattleUnit *source, BattleUnit *target, u16 item,
                         u8 mode, u8 flags);

void func_080B55CC(BattleActor *source, BattleActor *target, u16 action,
                   u16 equipment, u8 flags, u8 selection)
{
    SavedPosition saved_source;
    SavedPosition saved_target;
    u16 entry;
    u16 count;
    u16 attribute;
    s32 effect;
    s32 result;

    if (target == 0 || source == 0) {
        func_0802B8CC(func_0802D72C(1), 0, 0);
        return;
    }

    saved_source.x = source->unit->x;
    saved_source.y = source->unit->y;
    saved_source.direction = source->unit->direction;
    saved_target.x = target->unit->x;
    saved_target.y = target->unit->y;
    saved_target.direction = target->unit->direction;

    source->unit->x = source->x >> 5;
    source->unit->y = source->y >> 5;
    source->unit->direction = source->direction;
    target->unit->x = target->x >> 5;
    target->unit->y = target->y >> 5;
    target->unit->direction = target->direction;
    source->unit->direction =
        func_0809D6BC((s8)(target->unit->x - source->unit->x),
                      (s8)(target->unit->y - source->unit->y));

    if (selection != 0xFF) {
        func_0809920C(source, selection);
        func_0809915C(source, selection);
    }

    attribute = func_0812E6A4(target->unit);
    if (attribute == 10)
        attribute = 0;
    if (func_080C8240(source->unit) == func_080C8240(target->unit)
        && attribute == 4)
        attribute = 0;

    effect = func_08130200(source->unit, target->unit, action, equipment,
                           attribute, 2);

    switch (attribute) {
    case 4:
        if (func_0812F0E4(target->unit, target->unit->x, target->unit->y)
            && action != 0 && func_080CCD50(action, 0x1B)) {
            result = 0;
            effect = 0;
        } else {
            result = func_0812E0BC(source->unit, target->unit, action, 1,
                                   flags);
        }
        break;
    case 7:
        count = func_0812F0D8(target->unit, &entry);
        if (count == 0)
            entry = 0;
        if (action == 0
            && (!func_0812E1A8(target->unit, target->unit->x, target->unit->y,
                               source->unit->x, source->unit->y, entry, 1)
                || !func_0812F0E4(target->unit, target->unit->x,
                                  target->unit->y))) {
            result = func_0812EF94(source->unit, target->unit, entry, 1,
                                   action);
            break;
        }
        /* fallthrough */
    default:
        result = func_0812E0BC(source->unit, target->unit, action, 1, flags);
        break;
    }

    if (result > 100)
        result = 100;
    func_0802B8CC(func_0802D72C(1), result, effect);

    if (selection != 0xFF)
        func_0809915C(source, selection);

    source->unit->x = saved_source.x;
    source->unit->y = saved_source.y;
    source->unit->direction = saved_source.direction;
    target->unit->x = saved_target.x;
    target->unit->y = saved_target.y;
    target->unit->direction = saved_target.direction;
}
