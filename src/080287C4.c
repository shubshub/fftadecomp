#include "ffta.h"

/* Target: complete [0x080287C4, 0x080287EE), 42 bytes. */
typedef struct {
    u8 unknown_00[0x98];
    const u8 *entries;
} NavigationState080287C4;

typedef struct {
    s16 status;
} NavigationControl080287C4;

extern NavigationControl080287C4 *data_0200F438;

u8 func_080287C4(const NavigationState080287C4 *state)
{
    if (state->entries != 0 && state->entries[data_0200F438->status - 1] == 0)
        return 1;
    return 0;
}
