#include "ffta.h"

typedef struct {
    u8 unknown_00[5];
    u16 unknown_05 : 5;
    u16 limit : 8;
    u16 unknown_06 : 3;
} __attribute__((packed)) ProgressionInfo;

typedef struct {
    u8 unknown_00[0x2E7F];
    u8 progress[0][16];
} ProgressionState;

extern ProgressionState g_state_02000000;
extern const ProgressionInfo data_08528C24[];
extern u8 func_080CC3C8(u8 category, u8 index);

u16 func_080CC348(u8 category, u16 index, u8 count)
{
    u8 base_gain;
    s32 increase;
    u8 current;
    u8 limit;
    s32 total;

    index -= 0x16A;
    base_gain = func_080CC3C8(category, index);
    increase = base_gain * count;
    current = g_state_02000000.progress[category][0];
    total = increase + current;
    limit = data_08528C24[index].limit;
    if (total > limit) {
        if (current >= limit)
            return 0;
        return limit - current;
    }
    return increase;
}
