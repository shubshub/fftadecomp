#include "ffta.h"

typedef struct Node {
    u8 *record;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
} State;

extern u8 g_state_02000000[];
extern const u8 g_table_0855AE4C[][0x46];

u32 func_080D0AB0(u8 **output, u32 limit)
{
    u32 count = 0;
    Node *node = ((State *)g_state_02000000)->head;

    while (node != 0) {
        u8 *record = node->record;
        u16 identifier = record[0] | ((record[1] & 3) << 8);

        if ((u16)(identifier - 0x150) > 0x16 && !(record[2] & 0x1C)) {
            const u8 *definition = g_table_0855AE4C[identifier];
            u16 flags = definition[0x41] | (definition[0x42] << 8);

            if (!(flags & 0x400)) {
                if (output != 0)
                    *output++ = record;
                count++;
                if (count == limit)
                    break;
            }
        }
        node = node->next;
    }
    return count;
}
