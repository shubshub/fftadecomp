#include "ffta.h"

typedef struct Node0800C224 {
    u8 group;
    u8 unknown_01[0x1F];
    struct Node0800C224 *previous;
    struct Node0800C224 *next;
} Node0800C224;

typedef struct {
    u8 unknown_00[0x24];
    Node0800C224 *head;
} Group0800C224;

extern Group0800C224 g_records_02009000[];
extern void *data_02008FF8;
extern void func_08007170(void *owner, u8 *object);

#define UNLINK_NODE(node)                                               \
    do {                                                                \
        Node0800C224 *previous = (node)->previous;                      \
        Node0800C224 *next = (node)->next;                              \
                                                                        \
        if (previous != 0)                                              \
            previous->next = next;                                      \
        else                                                            \
            g_records_02009000[(node)->group].head = next;              \
        if (next != 0)                                                  \
            next->previous = previous;                                  \
    } while (0)

/* Complete 0800C224..0800C268, 68 bytes. Target:
30b5051c002d15d02c6a6b6a002c01d0636207e0094a297888004018c000243280180360002b00d01c6205480068291cfaf78cff30bc01bc0047000000900002f88f0002 */
void func_0800C224(Node0800C224 *node)
{
    if (node != 0) {
        UNLINK_NODE(node);
        func_08007170(data_02008FF8, (u8 *)node);
    }
}
