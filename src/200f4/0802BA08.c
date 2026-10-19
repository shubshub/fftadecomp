#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef struct {
    u8 unknown_00[0x10];
    Entry0802BA08 entries[32];
    u8 next;
} State0802BA08;

Entry0802BA08 *func_0802BA08(void)
{
    State0802BA08 **state = (State0802BA08 **)0x0200F440;
    Entry0802BA08 *entry = &(*state)->entries[(*state)->next++];

    (*state)->next &= 0x1F;
    return entry;
}
