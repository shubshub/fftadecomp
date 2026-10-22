#include "080D1C94.h"

u32 func_080D1C94(u8 **expired_records, u32 limit, u8 advance)
{
    CountdownState *state = (CountdownState *)g_state_02000000;
    Node *node;
    u32 count = 0;

    for (node = state->head; node != 0; node = node->next) {
        u8 *data = node->data;
        u16 identifier = data[0] | ((data[1] & 3) << 8);
        const u8 *definition;

        if (identifier_in_excluded_range(identifier) || (data[2] & 0x1C) != 0)
            continue;
        definition = g_table_0855AE4C[identifier];
        if ((definition[2] & 7) != 0)
            continue;
        if (advance_countdown(data, (definition[0x10] >> 3) & 7, advance)) {
            *expired_records++ = data;
            count++;
            if (count == limit)
                break;
        }
    }
    return count;
}
