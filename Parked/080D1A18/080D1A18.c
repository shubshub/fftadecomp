#include "080D1A18.h"

extern const u8 g_table_0855AE4C[][70];

u8 func_080C9540(u16 index);
void func_080CFCD0(u8 refresh);
u32 func_0800A5D4(u8 enabled);

u32 func_080D1A18(u8 *kind_out)
{
    Node *node;
    u8 flag = func_080C9540(0x36);

    func_080CFCD0(0);
    if (func_0800A5D4(0) != 0) {
        *kind_out = 1;
        for (node = ((SelectionStateView *)g_state_02000000)->head;
             node != 0; node = node->next) {
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
                ((SelectionStateView *)g_state_02000000)->selected_identifier =
                    record_identifier(record);
                return definition[0x45];
            } else {
                ((SelectionStateView *)g_state_02000000)->selected_identifier = identifier;
                return record_identifier(record);
            }
        }
    }
    return 0;
}
