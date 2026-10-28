#include "ffta.h"

typedef struct ListNode ListNode;

typedef struct {
    u32 key;
} Object0809AB5C;

typedef struct {
    u32 key;
    u32 unknown_04;
    Object0809AB5C *result;
} Search0809AB5C;

extern Object0809AB5C *func_080C7B74(const ListNode *node);

/* Complete [0x0809AB5C, 0x0809AB7C): 32 bytes, 15 instructions. */
s32 func_0809AB5C(const ListNode *node, Search0809AB5C *search)
{
    Object0809AB5C *object = func_080C7B74(node);
    s32 status;

    if (object->key != search->key) {
        status = 1;
    } else {
        search->result = object;
        status = 0;
    }
    return status;
}
