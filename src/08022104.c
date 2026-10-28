#include "ffta.h"

typedef struct ListNode08022104 ListNode08022104;
typedef struct ListContext08022104 ListContext08022104;

extern void *func_080C7B74(const ListNode08022104 *node);
extern ListNode08022104 *func_080C7BF4(ListContext08022104 *list, void *value);
extern void func_080C7A34(ListContext08022104 *list, ListNode08022104 *node);

/* Complete [0x08022104, 0x08022128): 36 bytes, 15 instructions. */
u32 func_08022104(ListNode08022104 *node, void *payload)
{
    ListContext08022104 *list = payload;
    void *value = func_080C7B74(node);
    ListNode08022104 *matching = func_080C7BF4(list, value);

    if (matching != 0)
        func_080C7A34(list, matching);
    return 1;
}
