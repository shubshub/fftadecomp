#include "ffta.h"

typedef struct {
    void *unit;
} UnitEntry;

extern s32 func_081304E0(void *unit);
extern s16 func_08130454(void *source, void *destination, s32 total);

/* 0x080B4294..0x080B42D2: 62 bytes. */
s16 func_080B4294(UnitEntry *source, UnitEntry *destination,
                   UnitEntry **entries, s32 count)
{
    s32 total = 0;
    s32 i;

    for (i = 0; i < count; i++)
        total += func_081304E0(entries[i]->unit);
    return func_08130454(source->unit, destination->unit, total);
}
