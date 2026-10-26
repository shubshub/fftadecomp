#include "ffta.h"

/* Target: complete [0x08148914, 0x08148A06), 242 bytes. */
typedef struct PriorityNode08148914 {
    void *object;
    s16 priority;
    s16 accumulated;
    u32 value_08;
    u32 value_0c;
    struct PriorityNode08148914 *left;
    struct PriorityNode08148914 *right;
    struct PriorityNode08148914 *parent;
} PriorityNode08148914;

typedef struct {
    PriorityNode08148914 nodes[16];
    PriorityNode08148914 *root;
    s32 value_1c4;
    s32 value_1c8;
    s32 count;
} PriorityTree08148914;

extern PriorityTree08148914 g_state_03005F30;
extern void func_08148B60(void *, u32, s8, u32);

#define WALK_PRIORITY_TREE(start, node, visit)                                 \
    do {                                                                     \
        PriorityNode08148914 *node = (start);                                 \
        PriorityNode08148914 *first = node;                                   \
        PriorityNode08148914 *previous = (PriorityNode08148914 *)-1;           \
        while (node) {                                                       \
            PriorityNode08148914 *right = node->right;                        \
            if (right && right != previous && node->left != previous) {       \
                previous = node;                                             \
                node = right;                                                \
                continue;                                                    \
            }                                                                \
            visit;                                                           \
            if (node->left && node->left != previous) {                       \
                previous = node;                                             \
                node = node->left;                                           \
                continue;                                                    \
            }                                                                \
            if (node == first)                                               \
                break;                                                       \
            previous = node;                                                 \
            node = node->parent;                                             \
        }                                                                    \
    } while (0)

void func_08148914(u8 amount)
{
    PriorityTree08148914 *tree;
    s32 budget;
    s32 remaining;

    if (!amount)
        return;
    tree = &g_state_03005F30;
    if (!tree->root)
        return;

    budget = amount;
    do {
        remaining = budget;
        WALK_PRIORITY_TREE(tree->root, node, {
            s32 after;

            if (remaining <= 0)
                goto restart_budget;
            if (node->priority > 254) {
                node->accumulated = 0xffff;
                goto dispatch;
            }
            after = remaining - node->priority;
            node->accumulated += node->priority;
            if (after <= 0)
                goto dispatch;
            remaining = after;
        });
restart_budget:
        budget = remaining;
    } while (remaining > 0);

dispatch:
    WALK_PRIORITY_TREE(tree->root, node, {
        if (node->accumulated)
            func_08148B60(node->object, node->value_08,
                          (s8)node->accumulated, node->value_0c);
    });
}
