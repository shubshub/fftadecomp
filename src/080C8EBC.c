/* func_080C8EBC: [0x080C8EBC, 0x080C9076), 442 bytes.
 * Writes a list of bytes for a unit into output and returns how many were
 * written.  A unit for which func_080C8240 or func_080C8260 holds, or whose
 * byte 4 is 0x0A, 9 or 0x5E, lists the selector 0x0C value of the record
 * func_080C94D0 finds for each index below count whose ability_points byte
 * is not zero, skipping zero values and values already listed.  Any other
 * unit lists the selector 0x0C value of record bit - 3 for each bit that
 * func_080C9540 reports set in the range its selector 3 value chooses.
 * The first list starts with 1 when neither func_080C8260 nor func_080C8240
 * holds, the second unless func_080C8228 holds.
 */
#include "ffta.h"

/* func_080C9F88 stores count from func_080C9ED8, whose largest result is
 * 0x8E; that bounds the index used here.  The next member known from
 * func_080C7EA4 is at 0xD0, so 0xCE and 0xCF are not accounted for.
 */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0x0A];
    u8 count;
    u8 unknown_35[0x0B];
    u8 ability_points[0x8E];
} Unit;

u8 func_080C8240(void *data);
u8 func_080C8260(const Unit *object);
u8 func_080C8194(const void *object, u8 category);
s32 func_080C7EA4(const void *object, u32 selector);
u8 func_080C94D0(u8 category, u16 value);
u32 func_080C8570(u8 first, u8 second, u8 selector);
u8 func_080C8228(const void *object);
u8 func_080C9540(u16 bitIndex);

u8 func_080C8EBC(Unit *unit, u8 *output)
{
    u8 *cursor = output;
    s32 index;

    if (func_080C8240(unit) || func_080C8260(unit) ||
        func_080C8194(unit, 0x0A) || func_080C8194(unit, 9) ||
        func_080C8194(unit, 0x5E)) {
        u8 category = func_080C7EA4(unit, 3);

        if (!func_080C8260(unit) && !func_080C8240(unit) &&
            (func_080C8194(unit, 0x0A) || func_080C8194(unit, 9) ||
             func_080C8194(unit, 0x5E)))
            *cursor++ = 1;
        for (index = 1; index < unit->count; index++) {
            if (unit->ability_points[index] != 0) {
                u8 entry = func_080C94D0(category, index);
                u8 value = func_080C8570(entry, entry, 0x0C);

                if (value != 0) {
                    u32 scan;
                    s32 unique = 1;

                    for (scan = 0; scan < cursor - output; scan++) {
                        if (output[scan] == value) {
                            unique = 0;
                            break;
                        }
                    }
                    if (unique == 1) {
                        *cursor++ = value;
                    }
                }
            }
        }
    } else {
        s32 first = 5;
        s32 last = 15;
        s32 entry;

        switch ((u32)func_080C7EA4(unit, 3)) {
        case 2:
            first = 16;
            last = 22;
            break;
        case 3:
            first = 23;
            last = 30;
            break;
        case 4:
            first = 31;
            last = 38;
            break;
        case 5:
            first = 39;
            last = 46;
            break;
        }
        if (!func_080C8228(unit))
            *cursor++ = 1;
        entry = first - 3;
        for (index = first; index <= last; index++, entry++) {
            if (func_080C9540(index))
                *cursor++ = func_080C8570(entry, entry, 0x0C);
        }
    }
    return cursor - output;
}
