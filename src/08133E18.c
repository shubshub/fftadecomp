#include "ffta.h"

/* Complete [0x08133E18, 0x08133F48): 304 bytes, 134 instructions. */

typedef struct {
    u8 unknown_00[0x19];
    u8 unknown_19;
    u8 unknown_1A[2];
} AbilityRecord;

extern const AbilityRecord data_0855187C[];
extern s32 func_0812F0D8(const void *object, u16 *entries);
extern s16 func_0812ED98(const void *unit, u16 entry);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_080C8280(const void *object);
extern u8 func_080CDB9C(const void *object);
extern u8 func_080CDBB4(const void *object);
extern u8 func_080CD944(const void *object);
extern u8 func_080CD95C(const void *object);
extern u8 func_080CDB3C(const void *object);
extern u8 func_080CDB54(const void *object);
extern u32 func_080CCD50(u16 identifier, u8 field);
extern s32 func_080CA7A4(u16 entry, u8 selector);

/* u8, as its caller src/08133F70.c declares it; it returns only 0 or 1. */
u8 func_08133E18(const void *unit, u16 ability, s8 kind)
{
    u16 items[2];   /* func_0812F0D8 fills two (func_0812E55C writes [0] and [1]) */
    const AbilityRecord *record;
    s16 cost;
    s16 remaining;

    func_0812F0D8(unit, items);
    record = &data_0855187C[ability];
    cost = func_0812ED98(unit, ability);
    /* s16: the ROM narrows the difference before the sign test
     * (lsls #16 at 0x08133E58). */
    remaining = func_080C7EA4(unit, 0x15) - cost;
    if (remaining < 0)
        return 0;
    if (kind < 0) {
        if (record->unknown_19 == 0)
            return 0;
    } else if (record->unknown_19 != (u8)kind) {   /* low byte: lsrs #24 at 0x08133E76 */
        return 0;
    }
    if (func_080C8280(unit))
        return 0;
    if (func_080CDB9C(unit))
        return 0;
    if (func_080CDBB4(unit))
        return 0;
    if (func_080CD944(unit))
        return 0;
    if (ability != 0x61 && func_080CD95C(unit))
        return 0;
    if (func_080CDB3C(unit) && func_080CCD50(ability, 0x14) == 0)
        return 0;
    if (func_080CDB54(unit) && func_080CCD50(ability, 0x18) == 0)
        return 0;
    switch (func_080CCD50(ability, 3)) {
    case 2:
        if (items[0] == 0)
            return 0;
        if (func_080CA7A4(items[0], 3) != 0xF)
            return 0;
        break;
    case 3:
        if (items[0] == 0)
            return 0;
        if (func_080CA7A4(items[0], 3) != 0xD && func_080CA7A4(items[0], 3) != 0xE)
            return 0;
        break;
    }
    return 1;
}
