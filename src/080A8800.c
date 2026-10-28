#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2C0];
    u8 count;
} EntryCount;

/* 0x080A8800..0x080A880A: 10 bytes. */
void func_080A8800(EntryCount *state, u8 count)
{
    state->count = count;
}
