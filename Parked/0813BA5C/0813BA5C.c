#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2F];
    u8 uses_table;
    u8 unknown_30[0x3BF8];
    u16 override_index;
    u8 selected;
} SelectionState0813BA5C;

typedef struct {
    u8 unknown_00[6];
    u8 selector;
    u8 unknown_07[5];
} SelectionEntry0813BA5C;

typedef struct __attribute__((packed)) {
    u8 value;
    u8 unknown_01[26];
} SelectionRecord0813BA5C;

extern const SelectionEntry0813BA5C g_table_08563A70[];
extern const SelectionRecord0813BA5C g_table_08564670[];

/* Complete [0x0813BA5C, 0x0813BB04): 168 bytes, 67 instructions. */
u32 func_0813BA5C(SelectionState0813BA5C *context, u8 mode)
{
    const SelectionEntry0813BA5C *entry;
    const SelectionRecord0813BA5C *record;

    if (mode == 0) {
        if (context->override_index != 0) {
            context->uses_table = 0;
            return context->override_index;
        }
        entry = &g_table_08563A70[context->selected];
        record = &g_table_08564670[entry->selector];
        context->uses_table = 1;
        return record->value;
    } else if (mode == 1) {
        context->uses_table = 0;
        return context->override_index;
    } else {
        entry = &g_table_08563A70[context->selected];
        record = &g_table_08564670[entry->selector];
        context->uses_table = 1;
        return record->value;
    }
}
