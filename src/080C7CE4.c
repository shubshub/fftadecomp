#include "ffta.h"

typedef struct ListNode {
    u8 unknown_00[8];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 unknown_00[4];
    ListNode *head;
} ListContext;

typedef u32 (*ListCallback)(ListNode *node, void *payload);

/* 080C7CE4..080C7D16: 50 bytes.
 * f0b5474680b40d1c90461f1c061c2c1c201c391c7af0b4fa002805d0a468002c00d17468a542
 * f3d108bc9846f0bc01bc0047
 *
 * The list arrives as a handle and is converted once.  The ROM moves r0 into
 * its own register only after the other three parameters are in place and
 * before `current` is set up, which is where this local sits; func_080C7908
 * and func_080C7C48 keep the same pointer in a second register the same way.
 */
void func_080C7CE4(void *list, ListNode *start, ListCallback callback,
                   void *payload)
{
    ListContext *context = list;
    ListNode *current = start;

    while (callback(current, payload) != 0) {
        current = current->next;
        if (current == 0)
            current = context->head;
        if (start == current)
            break;
    }
}
