#include "ffta.h"

typedef struct EffectRecord {
    u8 count;
    u8 unknown01;
    u8 pairs[9][2];
} EffectRecord;

typedef struct EffectObject {
    u8 unknown00[7];
    u8 marker;
    u8 unknown08[0x22];
    u16 entries[5];
} EffectObject;

extern const EffectRecord g_table_08520080[];

s32 func_080C7EA4(const void *object, u32 selector);
s32 func_080CA7A4(u16 entry, u8 selector);

u8 func_080CD1FC(const EffectObject *record, u8 index)
{
    u8 alternate = 0;
    s32 passes = 1;
    s32 slot;
    s32 pair;

    if (func_080C7EA4(record, 3) == 4) {
        if (index == 0x1A) {
            passes = 2;
            alternate = 0x21;
        } else if (index == 0x21) {
            passes = 2;
            alternate = 0x1A;
        }
    }

    while (--passes != -1) {
        for (slot = 0; slot < 5; slot++) {
            if (record->entries[slot]) {
                const EffectRecord *effects =
                    &g_table_08520080[func_080CA7A4(record->entries[slot], 0x12)];
                for (pair = 0; pair < effects->count; pair++) {
                    const u8 *effect = effects->pairs[pair];

                    if (effect[0] && effect[0] == record->marker &&
                        effect[1] == index)
                        return 1;
                }
            }
        }
        index = alternate;
    }
    return 0;
}
