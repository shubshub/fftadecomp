#include "ffta.h"

typedef struct TaskLinks {
    u8 unknown_00[8];
    const struct TaskLinks *sibling;
    u8 unknown_0C[4];
    const struct TaskLinks *child;
} TaskLinks;

u32 func_08005BC4(const void *object)
{
    const TaskLinks *node = object;
    u32 count = 0;

    node = node->child;
    while (node != 0) {
        count++;
        node = node->sibling;
    }
    return count;
}
