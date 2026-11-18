#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 job;
    u8 unknown_07[0x34];
    u8 selected;
} JobSelection;

typedef struct {
    u8 unknown_00[0x105];
    u8 chance_value;
    u8 unknown_106;
    u8 base_value;
} Unit080C13C8;

extern u32 func_0812F0CC(const void *unit, u16 *output);
extern u8 func_080CD50C(JobSelection *unit);
extern u32 func_08002804(void);

u16 func_080C13C8(Unit080C13C8 *unit)
{
    u16 equipment[5];
    u8 count = func_0812F0CC(unit, equipment);

    if (func_080CD50C((JobSelection *)unit) == 8 && count == 2)
        return 0;
    if (count == 1)
        return 0;
    if (unit->chance_value && (s16)((s16)func_08002804() % 101) <= 30)
        return unit->chance_value;
    if (unit->base_value)
        return unit->base_value;
    return 0;
}
