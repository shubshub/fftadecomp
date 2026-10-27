#include "ffta.h"

typedef struct ListNode080220E8 ListNode080220E8;
typedef struct TreeContext080220E8 TreeContext080220E8;

typedef struct Entry080220E8 {
    u8 unknown_00[0x12];
    u16 key;
} Entry080220E8;

extern void *func_080C7B74(const ListNode080220E8 *node);
extern ListNode080220E8 *func_080C7AB4(TreeContext080220E8 *context,
                                     void *value, s32 key);

/* Complete [0x080220E8, 0x08022102): 26 bytes, 11 instructions. */
u32 func_080220E8(ListNode080220E8 *node, void *payload)
{
    TreeContext080220E8 *context = payload;
    Entry080220E8 *entry = func_080C7B74(node);

    func_080C7AB4(context, entry, entry->key);
    return 1;
}
