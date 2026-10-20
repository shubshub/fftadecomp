#include "080D1218.h"
#include "script_entry.h"

extern u8 g_state_02002CB4[];
extern const u8 g_table_0855AE4C[][70];
extern const u8 g_table_085653F0[];

u8 func_080C95A8(u16 index);
u32 func_08002804(void);
Node *func_080CEF78(u8 mode, u16 category);

u8 func_080D1218(const SelectionRecord **output, u32 requested, u32 category)
{
    u32 remaining = requested;
    u8 marker = 0;
    Node *node;
    const SelectionRecord *record;
    const u8 *definition;
    u16 identifier;
    SelectionRecord *scratch;
    SelectionRecord *selected;
    s32 random;

    if (remaining == 0)
        return 0;
    node = ((State *)g_state_02000000)->head;
    if (node == 0)
        return 0;
    do {
        record = node->data;
        identifier = record_identifier(record);
        definition = g_table_0855AE4C[identifier];
        if (!identifier_in_excluded_range(identifier) && record->category == 0) {
            u16 flags = definition[0x41] | (definition[0x42] << 8);

            if (!(flags & 0x400) && (u8)((definition[2] & 7) - 4) <= 1 &&
                g_table_08563A70[definition[0x45]].unknown_00 == category) {
                *output++ = record;
                marker = 0x80;
                remaining--;
                if (remaining == 0)
                    break;
            }
        }
        node = node->next;
    } while (node != 0);
    if (remaining == 0)
        return requested - remaining + marker;
    node = ((State *)g_state_02000000)->head;
    while (node != 0) {
        record = node->data;
        identifier = record_identifier(record);
        definition = g_table_0855AE4C[identifier];
        if (!identifier_in_excluded_range(identifier) && record->category == 0) {
            u16 flags = definition[0x41] | (definition[0x42] << 8);

            if (!(flags & 0x400) && (u8)((definition[2] & 7) - 2) <= 1 &&
                g_table_08563A70[definition[0x45]].unknown_00 == category) {
                *output++ = record;
                remaining--;
                if (remaining == 0)
                    break;
            }
        }
        node = node->next;
    }
    if (remaining == 0)
        return requested - remaining + marker;
    definition = g_table_085653F0 + 38 * category;
    if (!(g_state_02002CB4[12 * category + 1] & 8))
        return requested - remaining + marker;
    scratch = (SelectionRecord *)0x03002850;
    (*(void (**)(void *, s32))0x0836D4B8)(scratch, 16);
    identifier = definition[4] | (definition[5] << 8);
    scratch->identifier_low = identifier;
    scratch->identifier_high = (scratch->identifier_high & ~3) | ((identifier >> 8) & 3);
    scratch->identifier_high &= 3;
    scratch->unknown_02_0 = 0;
    scratch->category = 0;
    scratch->unknown_03[0] = func_080C95A8(category + 0x14);
    random = (s16)func_08002804();
    random %= 0x136;
    scratch->unknown_03[3] = random;
    scratch->unknown_03[4] = (u32)random >> 8;
    node = find_excluded_record();
    if (node != 0) {
        remove_record(node->data);
        selected = find_free_record();
        append_record(selected, scratch);
    } else {
        selected = find_free_record();
        if (selected != 0) {
            append_record(selected, scratch);
        } else {
            node = func_080CEF78(2, 2);
            if (node != 0) {
                remove_record(node->data);
                selected = find_free_record();
                append_record(selected, scratch);
            } else {
                node = func_080CEF78(0, 3);
                if (node != 0) {
                    remove_record(node->data);
                    selected = find_free_record();
                    append_record(selected, scratch);
                }
            }
        }
    }
    if (selected != 0) {
        *output = selected;
        remaining--;
    }
    return requested - remaining + marker;
}
