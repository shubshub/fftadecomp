#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[10];
} FlagRecord;

extern FlagRecord g_state_02002CC0[];

u8 func_080CECF4(void)
{
    s32 count = 0;
    s32 index;

    for (index = 0; index < 30; index++) {
        if ((g_state_02002CC0[index].flags & 1) &&
            (g_state_02002CC0[index].flags & 2))
            count++;
    }
    return count;
}
