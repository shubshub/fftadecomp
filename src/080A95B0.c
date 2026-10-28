#include "ffta.h"

typedef struct ListNode ListNode;

typedef struct {
    u8 unknown_00[0x0E];
    s16 value_0E;
    s16 value_10;
    u8 unknown_12[6];
    const u8 *data;
    u8 unknown_1C;
    u8 enabled;
} Object080A95B0;

extern Object080A95B0 *func_080C7B74(const ListNode *node);

/* Complete [0x080A95B0, 0x080A95EA): 58 bytes, 28 instructions. */
s32 func_080A95B0(const ListNode *node, u32 *result)
{
    Object080A95B0 *object = func_080C7B74(node);

    if (object->enabled) {
        const u8 *data = object->data;
        s32 low = data[0];
        s32 value = (data[1] << 8) | low;

        if (value > object->value_0E || object->value_10 != 0) {
            *result = 1;
            return 0;
        }
    }
    return 1;
}
