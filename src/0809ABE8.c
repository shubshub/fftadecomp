#include "ffta.h"

typedef struct ListNode0809ABE8 ListNode0809ABE8;

typedef struct CallbackContext0809ABE8 {
    void *argument;
    u32 (*callback)(void *value, void *argument);
} CallbackContext0809ABE8;

extern void *func_080C7B74(const ListNode0809ABE8 *node);

/* Complete [0x0809ABE8, 0x0809ABFE): 22 bytes, 9 instructions. */
u32 func_0809ABE8(ListNode0809ABE8 *node, void *payload)
{
    CallbackContext0809ABE8 *context = payload;
    void *value = func_080C7B74(node);

    return context->callback(value, context->argument);
}
