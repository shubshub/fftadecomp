#include "ffta.h"

/* 0x08022148..0x08022164: 28 bytes. */
typedef struct ListNode ListNode;

typedef struct {
    u32 flags;
} FlagObject;

typedef struct {
    u16 clear;
    u16 set;
} FlagMasks;

extern FlagObject *func_080C7B74(const ListNode *node);

u32 func_08022148(ListNode *node, void *payload)
{
    const FlagMasks *masks = payload;
    FlagObject *object = func_080C7B74(node);
    u16 clear = masks->clear;
    u16 set = masks->set;

    object->flags = (object->flags & ~clear) | set;
    return 1;
}
