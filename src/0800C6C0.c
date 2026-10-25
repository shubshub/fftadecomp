#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} Struct0800C6C0;

/* 0x0800C6C0: 10 bytes; set bit 1 of the halfword at offset 0x0C. */
void func_0800C6C0(Struct0800C6C0 *state)
{
    state->flags |= 2;
}
