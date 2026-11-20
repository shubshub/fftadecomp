#include "movement_tile.h"

/* 0x0809ABB0..0x0809ABE6: 54 bytes / 26 instructions. */
u32 func_0809ABB0(ListNode *node, void *payload)
{
    TileSearch *context = payload;
    Actor *value = func_080C7B74(&node->object);

    if (context->x == value->unit->x &&
        context->y == value->unit->y) {
        context->match = value;
        return 0;
    }
    return 1;
}
