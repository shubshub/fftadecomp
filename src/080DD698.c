#include "ffta.h"

/* 0x080DD698..0x080DD6B6: 30 bytes. */
typedef struct {
    u32 unknown_00;
    u16 flags;
} Record080DD698;

extern void *func_080A880C(void *record);

u8 func_080DD698(Record080DD698 *record, u16 mask)
{
    Record080DD698 *state = func_080A880C(record);
    if (mask & state->flags)
        return 1;
    return 0;
}
