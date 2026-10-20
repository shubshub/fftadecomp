#include "script_entry.h"

typedef struct Node {
    u8 *record;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x16];
    u16 identifier;
    u8 unknown_18[0x10];
    u16 flags;
} ObjectState;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
} SelectionState;

extern u8 g_state_02000000[];
extern u8 g_state_02002E34[][6];
extern const u8 g_table_0855AE4C[][70];
extern const u8 g_table_08564670[][27];
extern const u8 g_table_08527E4A[][4];

u32 func_08002804(void);
u8 func_08036330(u8 selector);
u32 func_08036440(u8 value, u32 mode);
u32 func_080CF310(const void *record, const void *object, u8 enabled);

void func_080D0B48(u8 *record, void *object, u16 first, u16 second)
{
    ObjectState *state = object;
    const u8 *definition;
    u8 flags;
    u16 value;
    SelectionState *selection = (SelectionState *)g_state_02000000;
    Node *node;
    Node *tail;

    if (state != 0) {
        state->identifier = record[0] | ((record[1] & 3) << 8);
        state->flags |= 4;
    }
    record[4] = first;
    record[5] = second;
    flags = record[2] & ~0x1C;
    record[2] = flags;
    definition = g_table_0855AE4C[record[0] | ((record[1] & 3) << 8)];
    value = (definition[0x0F] >> 3) | ((definition[0x10] & 7) << 5);
    record[3] = value != 0 ? value : 0xFF;
    value = (definition[0x10] >> 6) | ((definition[0x11] & 0x3F) << 2);
    record[1] = (record[1] & 3) | ((value & 0x3F) << 2);
    record[2] = (flags & ~3) | ((value >> 6) & 3);

    if ((definition[2] & 7) == 1) {
        const u8 *category = definition + 0x45;
        const u8 *row_definition = g_table_08564670[g_table_08563A70[*category].selector];
        u8 *selected;
        s32 slot;

        for (slot = 0; slot < 5; slot++) {
            selected = g_state_02002E34[slot];
            if (!(selected[0] & 7))
                break;
        }
        (*(void (**)(void *, s32))0x0836D4B8)(selected, 6);
        selected[0] = (selected[0] & ~7) | ((slot + 1) & 7);
        selected[0] |= 8;
        selected[0] = (selected[0] & ~0x30) | ((row_definition[1] & 1) << 4);
        value = (row_definition[1] >> 2) & 7;
        selected[0] = (selected[0] & 0x3F) | ((value & 3) << 6);
        selected[1] = (selected[1] & ~3) | ((value >> 2) & 3);
        value = (row_definition[1] >> 5) | ((row_definition[2] & 0x1F) << 3);
        if (value & 0x80) {
            value &= ~0x80;
            selected[1] = (selected[1] & ~0x7C) | ((value & 0x1F) << 2);
        } else {
            value = func_08036330(value);
            selected[1] = (selected[1] & ~0x7C) | ((value & 0x1F) << 2);
        }
        value = (row_definition[1] >> 5) | ((row_definition[2] & 0x1F) << 3);
        selected[1] = (selected[1] & ~0x7C) | ((value & 0x1F) << 2);
        value = record[0] | ((record[1] & 3) << 8);
        selected[4] = value;
        flags = (selected[5] & ~1) | ((value >> 8) & 1);
        selected[5] = flags;
        value = *category;
        selected[2] = (selected[2] & 0x7F) | ((value & 1) << 7);
        selected[3] = (selected[3] & ~0x7F) | ((value >> 1) & 0x7F);
        selected[5] = (flags & 1) | 0xF0;
        value = func_08036330(g_table_08563A70[*category].unknown_00);
        selected[2] = (selected[2] & ~0x1F) | (value & 0x1F);
        selected[2] |= 0x20;
        if (func_08036440(selected[2] & 0x1F, 0)) {
            selected[1] |= 0x80;
        } else {
            for (slot = 0; slot < 5; slot++) {
                u8 *other = g_state_02002E34[slot];

                if ((other[0] & 7) && other != selected &&
                    (other[2] & 0x1F) == (selected[2] & 0x1F) &&
                    !(other[1] & 0x80)) {
                    selected[1] |= 0x80;
                    break;
                }
            }
        }
    } else if ((definition[2] & 7) == 0) {
        u32 result = func_080CF310(record, object, 1);

        if (result != 0) {
            const u8 *threshold = g_table_08527E4A[result];
            s16 random = (s16)func_08002804() % 256;

            if (random >= threshold[0])
                result = 0;
        }
        record[6] = result;
        record[7] = result >> 8;
    }

    node = selection->head;
    while (node->next != 0) {
        if (node->record == record)
            break;
        node = node->next;
    }
    tail = selection->head;
    while (tail->next != 0)
        tail = tail->next;
    if (selection->head == node && tail == node)
        return;
    if (tail == node)
        return;
    if (node->previous != 0) {
        node->previous->next = node->next;
        if (node->next != 0)
            node->next->previous = node->previous;
    } else if (node->next != 0) {
        node->next->previous = 0;
        selection->head = node->next;
    }
    tail->next = node;
    node->previous = tail;
    node->next = 0;
}
