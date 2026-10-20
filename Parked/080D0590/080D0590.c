#include "080D0590.h"
#include "script_entry.h"

extern u8 g_state_02000000[];
extern const u8 g_table_0855AE4C[][70];

u8 func_08036330(u8 selector);
u8 func_080C9540(u16 bitIndex);

u32 func_080D0590(SelectionRecord **output, u32 capacity, u32 filter)
{
    SelectionRecord **next_output = output;
    Node **head = (Node **)(g_state_02000000 + 0x28C8);
    Node *node;
    u32 count = 0;
    u8 unused = 0;
    u8 reserved_type_two = 0;
    u8 preferred = 1;
    u8 previous_miss = 0;
    s32 slot;

    (*(void (**)(void *, s32))0x0836D4B8)(output, capacity * 4);
    if (*head == 0)
        return 0;

    for (slot = 0; slot < 5; slot++) {
        if ((g_state_02000000[0x2E34 + slot * 6] & 7) == 0)
            unused++;
    }

    for (node = *head; node != 0; node = node->next) {
        SelectionRecord *record = node->data;
        u16 identifier = record_identifier(record);
        const u8 *definition = g_table_0855AE4C[identifier];

        if (identifier_in_excluded_range(identifier))
            continue;
        if (record->category != 0)
            continue;
        if (output_contains(output, record))
            continue;
        if (((definition[2] >> 3) & 7) == 2)
            reserved_type_two = 1;
        if (--capacity == 0)
            return count;
    }

    for (node = *head; node != 0; node = node->next) {
        SelectionRecord *record = node->data;
        const u8 *definition = g_table_0855AE4C[record_identifier(record)];
        u8 flags;
        u8 category_filter;

        if (definition[0x45] != 0 &&
            !func_08036330(g_table_08563A70[definition[0x45]].unknown_00))
            continue;
        flags = definition[2];
        if ((flags & 7) != 3 && (flags & 7) != 5 &&
            record_identifier(record) != 0x0F)
            continue;
        if (record->category == 0 || record->category > 2)
            continue;
        category_filter = definition_filter(definition);
        if (category_filter != 0 && category_filter != filter)
            continue;
        if (definition_flags(definition) & 0x400)
            continue;
        if (output_contains(output, record))
            continue;
        if ((flags & 7) == 1) {
            if (unused == 0)
                continue;
            unused--;
        }
        *next_output++ = record;
        count++;
        if (record->category != 0)
            record->category = 1;
        if (--capacity == 0)
            return count;
    }

    if (!reserved_type_two) {
        for (node = *head; node != 0; node = node->next) {
            SelectionRecord *record = node->data;
            u16 identifier = record_identifier(record);
            const u8 *definition = g_table_0855AE4C[identifier];
            u8 flags;
            u8 category_filter;

            if (identifier_in_excluded_range(identifier))
                continue;
            if (definition[0x45] != 0 &&
                !func_08036330(g_table_08563A70[definition[0x45]].unknown_00))
                continue;
            flags = definition[2];
            if (((flags >> 3) & 7) != 2)
                continue;
            if (record->category == 0 || record->category > 2)
                continue;
            category_filter = definition_filter(definition);
            if (category_filter != 0 && category_filter != filter)
                continue;
            if (output_contains(output, record))
                continue;
            if ((flags & 7) == 1) {
                if (unused == 0)
                    continue;
                unused--;
            }
            *next_output++ = record;
            count++;
            if (record->category != 0)
                record->category = 1;
            if (--capacity == 0)
                return count;
            break;
        }
    }

    do {
        for (node = *head; node != 0; node = node->next) {
            SelectionRecord *record = node->data;
            const u8 *definition = g_table_0855AE4C[record_identifier(record)];
            u16 identifier;
            u8 category_filter;

            if (definition[0x45] != 0 &&
                !func_08036330(g_table_08563A70[definition[0x45]].unknown_00))
                continue;
            identifier = record_identifier(record);
            if (identifier_in_excluded_range(identifier))
                continue;
            if (((definition[2] >> 3) & 7) != preferred)
                continue;
            if (identifier == 0x17F &&
                (func_080C9540(0x258) || func_080C9540(0x259) ||
                 func_080C9540(0x25A) || func_080C9540(0x25B) ||
                 func_080C9540(0x25C)))
                continue;
            if (record->category == 0 || record->category > 2)
                continue;
            category_filter = definition_filter(definition);
            if (category_filter != 0 && category_filter != filter)
                continue;
            if (output_contains(output, record))
                continue;
            if ((definition[2] & 7) == 1) {
                if (unused == 0)
                    continue;
                unused--;
            }
            *next_output++ = record;
            count++;
            if (record->category != 0)
                record->category = 1;
            if (--capacity == 0)
                return count;
            break;
        }
        if (node != 0) {
            previous_miss = 0;
        } else {
            if (previous_miss)
                break;
            previous_miss = 1;
        }
        preferred = !preferred;
    } while (capacity != 0);

    for (node = *head; node != 0; node = node->next) {
        SelectionRecord *record = node->data;

        if (record->category == 1 && !output_contains(output, record))
            record->category = 2;
    }
    return count;
}
