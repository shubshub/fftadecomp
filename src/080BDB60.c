#include "ffta.h"

typedef struct Node080BDB60 {
    u8 unknown_00[4];
    struct Node080BDB60 *next;
} Node080BDB60;

/* 0x080BDB60: 40 68 70 47 */
Node080BDB60 *func_080BDB60(const Node080BDB60 *node)
{
    return node->next;
}
