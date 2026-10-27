#include "ffta.h"

/* Target: complete [0x0804C834, 0x0804C858), 36 bytes. */
typedef struct {
    u8 unknown_00[0x0D];
    u8 active;
    u8 unknown_0E[0x0E];
} Entry0804C7A0;

extern void func_0804C7A0(Entry0804C7A0 *entries, u16 index);

void func_0804C834(Entry0804C7A0 *entries, s32 count)
{
    u16 index;

    for (index = 0; index < count; index++)
        func_0804C7A0(entries, index);
}
