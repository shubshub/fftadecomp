#include "080CEF78.h"

extern u8 g_state_02000000[];

u32 func_080CEECC(u16 identifier);

Node *func_080CEF78(u8 mode, u16 category)
{
    Node *head = ((State *)g_state_02000000)->head;
    Node *node;

    if (head == 0)
        return 0;
    if (mode != 0) {
        node = head;
        while (node->next != 0)
            node = node->next;
        while (node->previous != 0) {
            if (node->data->category == category) {
                if (mode == 1 && func_080CEECC(record_identifier(node->data)) == 0) {
                    if (identifier_in_excluded_range(record_identifier(node->data)) == 0)
                        return node;
                } else if (mode == 2) {
                    if (identifier_in_excluded_range(record_identifier(node->data)) == 0)
                        return node;
                }
            }
            node = node->previous;
        }
    } else {
        node = head;
        while (node->next != 0) {
            if (node->data->category == category) {
                if (identifier_in_excluded_range(record_identifier(node->data)) == 0)
                    return node;
            }
            node = node->next;
        }
    }
    return 0;
}
