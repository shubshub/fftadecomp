#include "ffta.h"

/* 0x08132DDC..0x08132E2A: 78 bytes. */
typedef struct {
    u8 unknown_00[6];
    u8 group;
    u8 unknown_07[0x2D];
    u8 count;
} EntryGroup;

typedef struct {
    u32 unknown_00;
    u32 identity;
} GroupEntry;

extern GroupEntry *func_080CD480(u8, u8);

u16 func_08132DDC(const EntryGroup *group, const GroupEntry *match)
{
    u32 count = group->count;
    u16 i;

    for (i = 1; i < count; ++i) {
        GroupEntry *entry = func_080CD480(group->group, i);

        if ((entry->identity & 0x00FFFFFF) ==
            (match->identity & 0x00FFFFFF))
            return i;
    }
    return 0;
}
