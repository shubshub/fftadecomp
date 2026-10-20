#include "ffta.h"

typedef struct EffectRecord {
    u8 count;
    u8 unknown01;
    u8 pairs[9][2];
} EffectRecord;

typedef struct {
    u8 unknown_00[7];
    u8 category;
    u8 unknown_08[0x35];
    u8 default_value;
} EffectObject;

extern const EffectRecord g_table_08520080[];

s32 func_080CA7A4(u16 entry, u8 selector);
void func_080CD620(void *object, u8 index);

void func_080CCF44(void *object, u16 entry)
{
    EffectObject *record = object;
    const EffectRecord *effects;
    s32 index;

    if (entry == 0)
        return;

    effects = &g_table_08520080[func_080CA7A4(entry, 0x12)];
    for (index = 0; index < effects->count; index++) {
        if (record->category == effects->pairs[index][0]) {
            u8 value = effects->pairs[index][1];

            if (record != 0) {
                u8 *values = (u8 *)record + 0x40;

                values[value] = 0x80 | values[value];
            }
            func_080CD620(record, effects->pairs[index][1]);
        } else if (effects->pairs[index][0] == 0xFF) {
            record->default_value = effects->pairs[index][1];
        }
    }
}
