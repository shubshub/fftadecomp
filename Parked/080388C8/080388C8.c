#include "ffta.h"

/* 0x080388C8..0x0803890A: 66 bytes. */
typedef struct {
    u16 key;
    u8 value;
    u8 unknown_03;
} LookupRecord080388C8;

extern u8 g_state_02000000[];

u8 func_080388C8(u16 key)
{
    u16 index = 0;
    u8 *state = g_state_02000000;

    for (; index < 361; index++) {
        if (*(u16 *)(index * sizeof(LookupRecord080388C8) + state + 0x1940) == key)
            return *(index * sizeof(LookupRecord080388C8) + state + 0x1942);
    }
    return 0;
}
