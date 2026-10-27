#include "ffta.h"

typedef struct ListNode08022128 ListNode08022128;
typedef struct ListContext08022128 ListContext08022128;
typedef u32 (*ListCallback08022128)(ListNode08022128 *node, void *payload);

struct ListObject08022128 {
    u32 unknown_00;
    ListContext08022128 *children;
    void *parent;
    u32 state;
};

extern struct ListObject08022128 *func_080C7B74(const ListNode08022128 *node);
extern void func_080C7CC0(ListContext08022128 *list,
                         ListCallback08022128 callback, void *payload);
extern u32 func_080221E4(ListNode08022128 *node, void *payload);

/* Complete [0x08022128, 0x08022148): 32 bytes, 11 instructions. */
u32 func_08022128(ListNode08022128 *node, void *payload)
{
    struct ListObject08022128 *object = func_080C7B74(node);

    object->state = 0;
    func_080C7CC0(object->children, func_080221E4, object);
    return 1;
}
