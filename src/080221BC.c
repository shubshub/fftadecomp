#include "ffta.h"

/* Target: complete [0x080221BC, 0x080221E4), 40 bytes. */
typedef struct ListNode ListNode;

typedef struct {
    u32 flags;
    u8 unknown_04[0x28];
    u32 value_2C;
} Object080221BC;

extern Object080221BC *func_080C7B74(const ListNode *node);

u32 func_080221BC(ListNode *node, void *payload)
{
    Object080221BC *object = func_080C7B74(node);

    if (object->value_2C != 0)
    {
        object->flags &= ~0x30000;
        object->flags &= ~0x80000;
    }
    return 1;
}
