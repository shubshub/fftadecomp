#include "080D0ED4.h"

extern const u8 g_table_0855AE4C[][70];
extern u8 g_state_02000000[];

void func_080CF118(u8 *data, u8 enabled);

void func_080D0ED4(u8 *data)
{
    const u8 *definition;

    func_080CF118(data, 0);
    definition = g_table_0855AE4C[data[0] | ((data[1] & 3) << 8)];
    if (definition[0x40] != 0) {
        SelectionRecord *record = (SelectionRecord *)data;

        record->category = 3;
        record->duration = definition[0x40];
    } else {
        Node *found = find_node(data);
        Node *previous;
        Node *next;

        previous = found->previous;
        next = found->next;
        if (previous != 0) {
            previous->next = next;
            if (next != 0)
                next->previous = previous;
        } else {
            u8 *state = g_state_02000000;

            if (next != 0)
                next->previous = previous;
            *(Node **)(state + 0x28C8) = next;
        }
        (*(void (**)(void *, u32))0x0836D4B8)(found->data, 16);
        found->data = 0;
    }
}
