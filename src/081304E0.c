#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 group;
    u8 unknown_07[0x35];
    u8 entry;
} Selection081304E0;

typedef struct {
    u8 unknown_00[4];
    u16 index;
    u8 type;
    u8 unknown_07;
} Entry081304E0;

typedef struct __attribute__((packed)) {
    u8 unknown_00;
    u8 flags : 5;
    u8 other_flags : 3;
    u8 unknown_02[2];
} Record081304E0;

extern const Entry081304E0 *func_080CD480(u8, u8);
extern const Record081304E0 data_0852736C[];

/* Complete [0x081304E0, 0x0813054A): 106 bytes including data and switch literals. */
u32 func_081304E0(const Selection081304E0 *selection)
{
    const Entry081304E0 *entry = func_080CD480(selection->group, selection->entry);
    if (entry->type == 5) {
        u32 offset = entry->index * sizeof(Record081304E0);
        const Record081304E0 *record = (const Record081304E0 *)((const u8 *)data_0852736C + offset);
        switch (record->flags) {
        case 0: return 5;
        case 1: return 8;
        case 2: return 10;
        case 3: return 12;
        case 4: return 15;
        }
    }
    return 0;
}
