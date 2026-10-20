#include "ffta.h"

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

extern SceneRecord g_state_02002FC4[12];

SceneRecord *func_080C83A4(void)
{
    SceneRecord *record = g_state_02002FC4;
    s32 index;

    for (index = 0; index < 12; index++, record++) {
        if (record->unknown_00[4] == 0)
            return record;
    }
    return 0;
}
