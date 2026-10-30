#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 flags : 6;
} Descriptor0813B9B8;

typedef struct ListNode0813B9B8 ListNode0813B9B8;
struct ListNode0813B9B8 {
    const Descriptor0813B9B8 *descriptor;
    u32 unknown_04;
    ListNode0813B9B8 *next;
};

typedef struct {
    u8 unknown_00[0x28C8];
    ListNode0813B9B8 *head;
} Context0813B9B8;

/* Complete [0x0813B9B8, 0x0813B9F8): 64 bytes, 27 instructions. */
u8 func_0813B9B8(const Context0813B9B8 *context)
{
    ListNode0813B9B8 *node;

    if (context->head == 0)
        return 0;

    for (node = context->head; node != 0; node = node->next) {
        if (node->descriptor->id == 0x17F)
            return 1;
    }
    return 0;
}
