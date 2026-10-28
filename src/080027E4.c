#include "ffta.h"

typedef struct {
    u32 value;
    u16 flags;
    u8 unknown_06[6];
} ClearEntry;

/* 080027E4..080027FA: 22 bytes, 11 instructions. */
void func_080027E4(ClearEntry *entries)
{
    s32 remaining;

    for (remaining = 0; remaining < 4; remaining++) {
        entries->value = 0;
        entries->flags = 0;
        entries++;
    }
}
