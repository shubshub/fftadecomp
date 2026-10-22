/* 0x080088D8 - 96 bytes */
#include "ffta.h"

typedef struct {
    u8 value;
    u8 count;
    u8 width;
    u8 enabled;
} OptionEntry;

typedef struct {
    u8 unknown_00[0x338];
    OptionEntry entries[10];
} OptionState;

typedef struct {
    u16 count;
    u16 width;
    u16 unknown_04[8];
} OptionDefinition;

extern const OptionDefinition g_table_0836D4D4[];
u8 func_080094BC(u8 index, u8 read_value);

void func_080088D8(void)
{
    OptionState *state = *(OptionState **)0x02009188;
    OptionEntry *entry = state->entries;
    const OptionDefinition *definition = g_table_0836D4D4;
    s32 index;

    for (index = 0; index < 10; index++, entry++, definition++) {
        entry->count = definition->count;
        entry->width = definition->width;
        if (index == 9) {
            entry->value = 0;
            entry->enabled = !func_080094BC((u8)index, 1);
        } else {
            entry->value = func_080094BC((u8)index, 1);
            entry->enabled = 1;
        }
    }
}
