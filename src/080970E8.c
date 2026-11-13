#include "ffta.h"

// Complete target [0x080970E8, 0x0809716C): 132 bytes, 62 instructions.
typedef struct Owner080970E8 Owner080970E8;

typedef struct {
    void *record;
    u8 unknown_04[0x58];
    s16 unknown_5C;
} Object080970E8;

typedef struct {
    u8 unknown_00[0x104];
    u8 unknown_104;
} Unit080970E8;

extern u32 func_08099CDC(Owner080970E8 *owner, Object080970E8 **entries);
extern u8 func_080CDCA4(void *record);
extern u8 func_080CE410(const void *record);
extern u8 func_0812E4A8(const void *record);

Object080970E8 *func_080970E8(Owner080970E8 *owner, Unit080970E8 *unit)
{
    Object080970E8 *entries[13];
    Object080970E8 *best;
    s32 lowest;
    s32 count;
    s32 i;

    count = func_08099CDC(owner, entries);
    best = 0;
    lowest = 0x400;
    for (i = 0; i < count; i++) {
        if (entries[i]->unknown_5C < lowest && func_080CDCA4(entries[i]->record) &&
            unit->unknown_104 == func_080CE410(entries[i]->record) &&
            func_0812E4A8(entries[i]->record)) {
            lowest = entries[i]->unknown_5C;
            best = entries[i];
        }
    }
    return best;
}
