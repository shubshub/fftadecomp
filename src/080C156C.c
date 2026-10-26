#include "ffta.h"

typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} UnitCoordinates;

typedef struct {
    UnitCoordinates *unit;
    u8 unknown_04[4];
    u16 x;
    u8 unknown_0A[2];
    u16 y;
} MapEntry;

extern void func_080C127C(u32 first, u32 second, MapEntry *entry,
                         u32 fourth, u32 fifth, u32 sixth);

void func_080C156C(u32 first, u32 second, MapEntry *entry,
                   u32 fourth, u32 fifth, u32 sixth)
{
    u8 old_x = entry->unit->x;
    u8 old_y = entry->unit->y;

    entry->unit->x = entry->x >> 5;
    entry->unit->y = entry->y >> 5;
    func_080C127C(first, second, entry, fourth, fifth, sixth);
    entry->unit->x = old_x;
    entry->unit->y = old_y;
}
