#include "080D17C4.h"
#include "script_entry.h"

extern u8 g_state_02002E34[][6];
extern const u8 g_table_0855AE4C[][70];

u8 func_080C9540(u16 index);
u32 func_0800A5D4(u8 enabled);

u32 func_080D17C4(u32 filter, u8 slot_value, u8 *kind_out)
{
    SelectionStateView *state = (SelectionStateView *)g_state_02000000;
    Node *node;
    u8 flag;
    s32 index;

    for (index = 0; index < 5; index++) {
        u8 *slot = g_state_02002E34[index];

        if ((slot[0] & 7) != 0 && !(slot[1] & 0x80) &&
            (slot[2] & 0x1F) == slot_value) {
            *kind_out = 3;
            return (slot[2] >> 7) | ((slot[3] & 0x7F) << 1);
        }
    }
    flag = func_080C9540(0x36);
    if (func_0800A5D4(1) != 0) {
        *kind_out = 1;
        for (node = state->head; node != 0; node = node->next) {
            const SelectionRecord *record = node->data;
            u16 identifier = record_identifier(record);
            const u8 *definition;
            u8 kind;

            if (identifier_in_excluded_range(identifier) || record->category != 0)
                continue;
            definition = g_table_0855AE4C[identifier];
            kind = definition[2] & 7;
            if (kind != 4 && kind != 5)
                continue;
            if (flag != 0 && identifier == 0x1A)
                continue;
            if (identifier == 0x18D) {
                if (func_080C9540(0x48C) != 0)
                    remove_record(record);
            } else if (definition[0x45] != 0) {
                *kind_out = 2;
                state->selected_identifier = record_identifier(record);
                return definition[0x45];
            } else {
                state->selected_identifier = identifier;
                return record_identifier(record);
            }
        }
    }
    for (node = state->head; node != 0; node = node->next) {
        const SelectionRecord *record = node->data;
        u16 identifier = record_identifier(record);
        const u8 *definition;
        u8 kind;

        if (identifier_in_excluded_range(identifier) || record->category != 0)
            continue;
        definition = g_table_0855AE4C[identifier];
        if (definition[0x45] == 0 ||
            g_table_08563A70[definition[0x45]].unknown_00 != filter)
            continue;
        kind = definition[2] & 7;
        if ((kind != 4 && kind != 5) ||
            (definition[0] | (definition[1] << 8)) == 0x1A)
            continue;
        *kind_out = 2;
        return definition[0x45];
    }
    *kind_out = 0;
    return 0;
}
