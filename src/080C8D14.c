// func_080C8D14: [0x080C8D14, 0x080C8EBC), 424 bytes.
// Collects the abilities an item grants into a 0x1C-byte list,
// grouping consecutive entries for multi-part ability kinds.
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u16 id;
} AbilityInfo;

typedef struct {
    u8 unknown_00[4];
    u8 category;
    u8 unknown_05[0x2F];
} CategoryRecord;

typedef u8 ItemAbility[2];

typedef struct {
    u8 count;
    u8 unknown_01;
    ItemAbility entries[9];
} ItemAbilities;

typedef struct {
    u16 id;
    u16 kind;
    u8 sources[4];
} GrantedAbility;

typedef struct {
    u16 count;
    u16 unknown_02;
    GrantedAbility entries[3];
} GrantedAbilities;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern const ItemAbilities g_table_08520080[];
extern const CategoryRecord g_table_08521A14[];
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern const AbilityInfo *func_080CD480(u8 category, u8 ability);

u8 func_080C8D14(u16 item, GrantedAbilities *out)
{
    const ItemAbilities *table;
    const CategoryRecord *record;
    const AbilityInfo *info;
    s32 i;
    s32 n;
    s32 k;

    g_callbacks_0836D4B8[0](out, 0x1C);
    table = &g_table_08520080[func_080CA7A4(item, 0x12)];
    if (table->count == 0)
        return 0;
    if (table->count == 1) {
        record = &g_table_08521A14[table->entries[0][0]];
        info = func_080CD480(record->category, table->entries[0][1]);
        out->count = 1;
        out->entries[0].id = info->id;
        out->entries[0].kind = 1;
        out->entries[0].sources[0] = table->entries[0][0];
        return 1;
    }
    n = 0;
    for (i = 0; i < table->count; n++) {
        record = &g_table_08521A14[table->entries[i][0]];
        info = func_080CD480(record->category, table->entries[i][1]);
        out->count++;
        out->entries[n].id = info->id;
        switch (table->entries[i][0]) {
        case 5:
        case 9:
        case 11:
        case 22:
            out->entries[n].kind = 2;
            for (k = 0; k < 2; k++)
                out->entries[n].sources[k] = table->entries[i++][0];
            break;
        case 7:
        case 8:
            out->entries[n].kind = 3;
            for (k = 0; k < 3; k++)
                out->entries[n].sources[k] = table->entries[i++][0];
            break;
        default:
            out->entries[n].kind = 1;
            out->entries[n].sources[0] = table->entries[i][0];
            i++;
            break;
        }
    }
    return out->count;
}
