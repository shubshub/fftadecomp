#include "ffta.h"

typedef struct ListNode ListNode;

typedef struct {
    u32 flags;
    u8 unknown_04[0x28];
    u32 value_2C;
} ListObject;

extern ListObject *func_080C7B74(const ListNode *node);

/* 08022194..080221BA: 38 bytes. */
u32 func_08022194(ListNode *node, u8 *payload)
{
    ListObject *object = func_080C7B74(node);

    if ((object->flags & 0x80000) == 0 && object->value_2C != 0)
        *payload = 0;
    return 1;
}
