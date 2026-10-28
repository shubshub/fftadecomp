#include "ffta.h"

/* 0x0804C7A0..0x0804C7B2: 18 bytes. */
typedef struct {
    u8 unknown_00[0x0D];
    u8 active;
    u8 unknown_0E[0x0E];
} Entry0804C7A0;

void func_0804C7A0(Entry0804C7A0 *entries, u16 index)
{
    entries[index].active = 0;
}
