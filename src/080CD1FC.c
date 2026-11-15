#include "ffta.h"

typedef struct EffectPair {
    u8 marker;
    u8 value;
} __attribute__((packed)) EffectPair;

typedef struct EffectRecord {
    u8 count;
    u8 unknown_01;
    EffectPair pairs[9];
} EffectRecord;

typedef struct EffectObject {
    u8 unknown_00[7];
    u8 group;
    u8 unknown_08[0x22];
    u16 entries[5];
} EffectObject;

extern const EffectRecord g_table_08520080[];

s32 func_080C7EA4(const void *object, u32 selector);
s32 func_080CA7A4(u16 entry, u8 selector);

/* Complete target: [0x080CD1FC, 0x080CD2C4), 200 bytes, including the table literal. */
u8 func_080CD1FC(const EffectObject *data, u8 value)
{
    u8 alternate = 0;
    s32 passes = 1;
    s32 slot;
    s32 index;

    if (func_080C7EA4(data, 3) == 4) {
        if (value == 0x1A) {
            passes = 2;
            alternate = 0x21;
        } else if (value == 0x21) {
            passes = 2;
            alternate = 0x1A;
        }
    }

    while (--passes != -1) {
        for (slot = 0; slot < 5; slot++) {
            if (data->entries[slot] != 0) {
                const EffectRecord *effects =
                    &g_table_08520080[func_080CA7A4(data->entries[slot], 0x12)];

                for (index = 0; index < effects->count; index++) {
                    u8 marker = effects->pairs[index].marker;

                    if (marker != 0 && marker == data->group &&
                        effects->pairs[index].value == value)
                        return 1;
                }
            }
        }
        value = alternate;
    }
    return 0;
}
