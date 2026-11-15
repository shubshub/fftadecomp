#include "ffta.h"

/* 08018E20..08018E94: 116 bytes, 50 instructions (pool words at
 * 0x08018E3C, 0x08018E40 and 0x08018E7C). */

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
} SelectedResource08018E20;

typedef struct {
    const SelectedResource08018E20 *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
} ResourceSelection08018E20;

typedef struct {
    const u8 *text;
    u8 unknown_04[0x12];
    u16 id;
    u8 unknown_18[0xF0];
} UnitRecord08018E20;

typedef struct {
    UnitRecord08018E20 units[24];
    u8 unknown_18C0[0x790];
    ResourceSelection08018E20 selection;
} State08018E20;

extern State08018E20 g_state_02000080;
extern const u8 *const g_table_08526680[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

u32 func_08018E20(u8 *destination)
{
    const UnitRecord08018E20 *record = g_state_02000080.units;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        ResourceSelection08018E20 *selection = &g_state_02000080.selection;

        if (record->id == (selection->current
                           ? selection->current->id : selection->id))
            break;
    }
    if (index == 24)
        func_08018C24(destination, g_table_08526680[0]);
    else
        func_08018C24(destination, record->text);
    return 0;
}
