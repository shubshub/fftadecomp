#include "ffta.h"

/* 0x08022164..0x08022194: 48 bytes. */
typedef struct ListNode ListNode;
typedef struct TreeContext TreeContext;
typedef struct TreeNode TreeNode;

typedef struct {
    u16 lower;
    u16 upper;
} KeyRange;

typedef struct {
    u8 unknown_00[0x12];
    u16 key;
    u8 unknown_14[0x24];
    void *active;
} KeyObject;

typedef struct {
    const KeyRange *range;
    TreeContext *destination;
} FilterContext;

extern KeyObject *func_080C7B74(const ListNode *node);
extern TreeNode *func_080C7AB4(TreeContext *context, void *value, s32 key);

u32 func_08022164(ListNode *node, void *payload)
{
    FilterContext *context = payload;
    KeyObject *object = func_080C7B74(node);
    const KeyRange *range = context->range;

    if (range->lower > object->key || range->upper <= object->key) {
        return 1;
    }
    if (object->active) {
        func_080C7AB4(context->destination, object, object->key);
    }
    return 1;
}
