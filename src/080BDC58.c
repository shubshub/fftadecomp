#include "ffta.h"

/* 0x080BDC58..0x080BDC98: 64 bytes, 32 Thumb instructions.
 *
 * Unlinks a node from the chain of the grid cell at (x, y).
 *
 * `next` holds the link for the two loop tests only: the ROM reads the link
 * again to advance (0x080BDC7E) and again for the test after the loop
 * (0x080BDC8A).
 */
typedef struct Node {
    u8 unknown_00;
    u8 type;
    u8 unknown_02[2];
    struct Node *next;
} Node;

void func_080BDC58(u8 *grid, Node *node, u8 x, u8 y)
{
    u32 offset = x * 4 + y * 64;
    Node **cell = (Node **)(grid + offset);
    Node *head = *cell;
    Node *next;

    if (head == (Node *)-1)
        return;
    if (head == 0)
        return;
    if (head == node) {
        *cell = 0;
    } else {
        while ((next = head->next) != 0 && next != node)
            head = head->next;
        if (head->next == node)
            head->next = node->next;
    }
}
