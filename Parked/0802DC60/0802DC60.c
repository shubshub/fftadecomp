#include "ffta.h"

typedef struct {
    u8 owner : 4;
    u8 option : 7;
    u8 active : 1;
    u8 type : 4;
    u8 rank : 3;
    u8 unknown_13 : 5;
    u8 timer;
} __attribute__((packed)) OptionRecord;

typedef struct {
    u8 unknown_00[0xD];
    u8 type;
    u8 unknown_0E[2];
} OptionDefinition;

extern OptionRecord data_02003C3C[24];
extern const OptionDefinition g_table_08528F34[];

OptionRecord *func_0802DF50(void);
void *func_0802DE58(OptionRecord *record);
u32 func_0802DF90(void *member);

/* Complete target: [0x0802DC60, 0x0802DD58), 248 bytes. */
void func_0802DC60(u8 owner, u8 option, u8 active)
{
    OptionRecord *record = func_0802DF50();
    OptionRecord *entry;
    void *member;
    s32 matches;
    s32 remaining;

    if (record == 0 || owner == 0xFF) {
        return;
    }

    entry = data_02003C3C;
    matches = 0;
    for (remaining = 23; remaining >= 0; remaining--, entry++) {
        if (entry->option != 0 && entry->owner == owner) {
            matches++;
        }
    }
    if (matches > 1) {
        return;
    }

    record->owner = owner;
    record->option = option;
    record->active = active > 0;
    record->type = g_table_08528F34[option].type;
    member = func_0802DE58(record);
    if (member == 0) {
        record->rank = 0;
    } else {
        record->rank = func_0802DF90(member);
    }
    record->unknown_13 = 0;
    record->timer = 0;
}
