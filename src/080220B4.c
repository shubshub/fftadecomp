#include "ffta.h"

typedef struct ListNode ListNode;
typedef struct ListContext ListContext;

typedef struct {
    void *unknown_00;
    ListContext *context;
} Object080220B4;

extern Object080220B4 *func_080C7B74(const ListNode *node);
extern void *func_080C7908(ListContext *context);

/* 0x080220B4 - 22 bytes.
 * Target: 00b5a5f05dfd002802d04068a5f022fc012002bc0847
 */
u32 func_080220B4(ListNode *node, void *payload)
{
    Object080220B4 *object = func_080C7B74(node);

    if (object != 0)
        func_080C7908(object->context);
    return 1;
}
