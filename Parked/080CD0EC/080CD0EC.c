#include "ffta.h"

// Complete [0x080CD0EC, 0x080CD1FA): 270 bytes, including the three-word
// literal pool (g_table_0851BA84, g_callbacks_0836D4B8, g_table_08520080).

typedef struct EffectPair {
    u8 marker;
    u8 value;
} __attribute__((packed)) EffectPair;

typedef struct EffectRecord {
    u8 count;
    u8 unknown_01;
    EffectPair pairs[9];
} EffectRecord;

typedef struct SlotEntry {
    u8 unknown_00[6];
    u8 group;
    u8 unknown_07;
} SlotEntry;

typedef struct SlotOwner {
    u8 unknown_00[7];
    u8 category;
    u8 unknown_08[0x22];
    u16 effects[5];
    u8 slot_count;
    u8 unknown_35[0xB];
    u8 enabled[0];
} SlotOwner;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern const SlotEntry *const g_table_0851BA84[];
extern const BufferInitializer g_callbacks_0836D4B8[];
extern const EffectRecord g_table_08520080[];

s32 func_080C7EA4(const void *unit, u32 selector);
s32 func_080CA7A4(u16 entry, u8 selector);

u8 func_080CD0EC(SlotOwner *owner, u8 *out, u8 group)
{
    u8 found[0x20];
    u8 *cursor = out;
    const SlotEntry *entry = g_table_0851BA84[func_080C7EA4(owner, 3)];
    const EffectRecord *effects;
    s32 count;
    s32 i;
    s32 j;

    entry++;
    g_callbacks_0836D4B8[0](found, 0x20);
    count = 0;

    for (i = 0; i < 5; i++) {
        if (owner->effects[i] == 0)
            continue;
        effects = &g_table_08520080[func_080CA7A4(owner->effects[i], 0x12)];
        for (j = 0; j < effects->count; j++) {
            if (effects->pairs[j].marker != 0
                && effects->pairs[j].marker == owner->category)
                found[count++] = effects->pairs[j].value;
        }
    }

    for (i = 1; i < owner->slot_count; i++, entry++) {
        if (entry->group != group)
            continue;
        if (owner->enabled[i]) {
            *cursor++ = i;
        } else {
            for (j = 0; j < count; j++) {
                if (found[j] == i)
                    *cursor++ = i;
            }
        }
    }

    return cursor - out;
}
