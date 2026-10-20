#include "ffta.h"

typedef struct EffectRecord {
    u8 count;
    u8 unknown01;
    u8 pairs[9][2];
} EffectRecord;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

typedef struct {
    u8 unknown_00[6];
    u8 category;
    u8 group;
    u8 unknown_08[0x22];
    u16 entries[5];
} EntryObject;

extern const EffectRecord g_table_08520080[];

s32 func_080CA7A4(u16 entry, u8 selector);
const u8 *func_080CD480(u8 first, u8 second);
u8 func_080CD1FC(const void *object, u8 index);
void func_080CD620(void *object, u8 index);
u8 func_080C8240(void *data);
u8 func_080C8260(const FlaggedObject *object);
u8 func_080C9540(u16 bitIndex);
void func_080CAB24(u16 entry, u8 increment);
void func_080CCF44(void *object, u16 entry);

void func_080CAF78(void *object, u16 entry, u8 slot)
{
    EntryObject *data = object;
    u16 old = data->entries[slot];

    if (old != 0) {
        const EffectRecord *effects;
        u8 *actions;
        s32 index;

        if (old == entry)
            return;
        effects = &g_table_08520080[func_080CA7A4(old, 0x12)];
        actions = (u8 *)data + 0x34;
        data->entries[slot] = 0;
        for (index = 0; index < effects->count; index++) {
            u8 marker = effects->pairs[index][0];

            if (marker != 0) {
                if (marker == data->group) {
                    u8 value = effects->pairs[index][1];
                    u8 level = ((u8 *)data + 0x40)[value] & 0x7F;

                    if (level < func_080CD480(data->category, value)[7] &&
                        !func_080CD1FC(data, value)) {
                        if (actions[8] == value)
                            actions[8] = 0;
                        else if (actions[7] == value)
                            actions[7] = 0;
                        else if (actions[6] == value)
                            actions[6] = 0;
                        actions[0xC + value] &= 0x7F;
                        func_080CD620(data, value);
                    }
                } else if (marker == 0xFF && func_080CA7A4(old, 3) == 0x1B) {
                    actions[9] = 0;
                }
            }
        }
    }
    if (!func_080C8240(data) &&
        !func_080C8260((const FlaggedObject *)data) &&
        !func_080C9540(0x3E)) {
        if (old != 0)
            func_080CAB24(old, 0);
        if (entry != 0)
            func_080CAB24(entry, 1);
    }
    data->entries[slot] = entry;
    func_080CCF44(data, entry);
}
