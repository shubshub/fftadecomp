#include "ffta.h"

typedef struct {
    u8 identifier_low;
    u8 identifier_high;
    u8 flags;
    u8 unknown_03[13];
} ListRecord;

typedef struct Node {
    ListRecord *record;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
} State;

extern u8 g_state_02000000[];

u32 func_080CEDC8(void *source)
{
    Node *node = ((State *)g_state_02000000)->head;
    ListRecord *record;
    ListRecord *candidate;
    s32 index;

    while (node->next != 0)
        node = node->next;
    while (node->previous != 0) {
        record = node->record;
        if (record->flags & 0x1C)
            break;
        node = node->previous;
    }
    if (node->previous == 0)
        return 0;

    node->previous->next = node->next;
    if (node->next != 0)
        node->next->previous = node->previous;
    (*(void (**)(void *, u32))0x0836D4B8)(record, sizeof(*record));
    (*(void (**)(void *, u32))0x0836D4B8)(node, sizeof(*node));

    record = 0;
    candidate = (ListRecord *)0x020021C8;
    for (index = 0; index < 64; index++, candidate++) {
        if ((candidate->identifier_low | ((candidate->identifier_high & 3) << 8)) == 0) {
            record = candidate;
            break;
        }
    }
    ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(record, source, sizeof(*record));

    node = (Node *)0x020025C8;
    for (index = 0; index < 64; index++, node++) {
        if (node->record == 0)
            break;
    }
    if (index == 64)
        node = 0;

    {
        State *state = (State *)g_state_02000000;

        if (state->head != 0) {
            node->record = record;
            node->previous = 0;
            node->next = state->head;
            state->head->previous = node;
            state->head = node;
        } else {
            state->head = node;
            node->record = record;
            node->next = 0;
            node->previous = 0;
        }
    }
    return 1;
}
