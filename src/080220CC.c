#include "ffta.h"

struct ListNode080220CC;

extern void *func_080C7B74(const struct ListNode080220CC *node);
extern void func_08007170(void *owner, u8 *object);

u32 func_080220CC(struct ListNode080220CC *node, void *owner)
{
    u8 *payload = func_080C7B74(node);

    if (payload)
        func_08007170(owner, payload);
    return 1;
}
