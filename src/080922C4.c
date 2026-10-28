#include "ffta.h"

typedef struct {
    u8 unknown_00[0x64];
    u16 state;
} State080922C4;

/* 0x080922C4..0x080922CC: 8 bytes, 4 instructions. */
void func_080922C4(State080922C4 *object)
{
    object->state = 3;
}
