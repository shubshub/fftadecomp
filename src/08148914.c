#include "ffta.h"

/* Complete [0x08148914, 0x08148A06): 242 bytes, 115 instructions and two
 * literal words.
 * f0b50006020e002a70d00e48e0214900431819688446002968d0101c1f1c3a68041c161c
 * 01256d42002a2fd05369002b0ad0ab4208d01069a84205d0151c1a1cf2e70000305f0003
 * 002c1fdd91880423d05efe2804dd0148d0801ae0ffff00000423d05e231ad4880819d080
 * 002b10dd1c1c1069002804d0a84202d0151c021cd2e7b24202d0151c9269cde7201c002c
 * c5dce020400060440468261c01256d42002c23d06169002907d0a94205d02069a84202d0
 * 251c0c1cf2e7e2880621605e002806d02068a16812061216e36800f0bdf82069002804d0
 * a84202d0251c041cdee7b44202d0251ca469d9e7f0bc01bc0047
 * Shares an amount out over the priority tree that func_08148860
 * (src/08148860.c) builds, walking it highest priority first and starting
 * over while some is left, then hands each node its share. */

typedef struct PriorityNode {
    void *object;
    s16 priority;
    s16 value_06;
    u32 value_08;
    u32 value_0C;
    struct PriorityNode *left;
    struct PriorityNode *right;
    struct PriorityNode *parent;
} PriorityNode;

typedef struct {
    PriorityNode nodes[16];
    PriorityNode *root;
    s32 value_1C4;
    s32 value_1C8;
    s32 count;
} PriorityTree;

extern PriorityTree g_state_03005F30;

u32 func_08148B60(void *object, u32 value_08, s8 share, u32 value_0C);

void func_08148914(u8 amount)
{
    s32 budget;
    s32 remaining;

    if (amount == 0)
        return;
    if (g_state_03005F30.root == 0)
        return;

    budget = amount;
    do {
        PriorityNode *node = g_state_03005F30.root;
        PriorityNode *first;
        PriorityNode *prev;
        s32 after;

        remaining = budget;
        first = node;
        prev = (PriorityNode *)-1;
        while (node != 0) {
            if (node->right != 0 && node->right != prev
                && node->left != prev) {
                prev = node;
                node = node->right;
                continue;
            }
#ifdef BUGFIX
            /* Climbing back from the left subtree: the node was charged on
               the way down (see the BUG note in the walk below). */
            if (node->left == prev)
                goto climb;
#endif
            /* This exit stores the budget as the walk's end does.  The ROM
               keeps one copy of the store, adds r0, r4, #0 at 0x081489A0,
               where cross-jumping merged it with the end's: all three exits
               reach it (0x0814893E, 0x0814895E, 0x08148998). */
            if (remaining <= 0) {
                budget = remaining;
                goto next;
            }
            if (node->priority > 254) {
                node->value_06 = 0xFFFF;
                goto dispatch;
            }
            after = remaining - node->priority;
            node->value_06 += node->priority;
            if (after <= 0)
                goto dispatch;
            remaining = after;
            if (node->left != 0 && node->left != prev) {
                prev = node;
                node = node->left;
                continue;
            }
#ifdef BUGFIX
        climb:
#endif
            if (node == first)
                break;
            prev = node;
            node = node->parent;
        }
        budget = remaining;
    next:;
    } while (budget > 0);

dispatch:
    {
        PriorityNode *node = g_state_03005F30.root;
        PriorityNode *first = node;
        PriorityNode *prev = (PriorityNode *)-1;

        while (node != 0) {
            if (node->right != 0 && node->right != prev
                && node->left != prev) {
                prev = node;
                node = node->right;
                continue;
            }
            /* BUG: a node is visited a second time when the walk climbs back
               from its left child.  The test above only keeps the walk from
               going right again (left == prev, cmp r0, r5 at 0x081489C4) and
               nothing skips the visit, so func_08148B60 runs twice for a node
               that has a share and a left child (bl at 0x081489E2).  The first
               walk has the same shape (0x0814894C) and charges such a node
               twice (0x0814897A-0x0814897E).  The game never builds such a
               tree: func_0809A5E0, the only caller, inserts one node and walks
               at once, and func_08096E78 empties the tree (func_08148830)
               before each script step, which makes at most one such call, so
               every walk sees a single node.  docs/bugs/08148914/ has the
               case. */
#ifdef BUGFIX
            if (node->left != prev)
#endif
            if (node->value_06 != 0)
                func_08148B60(node->object, node->value_08, node->value_06,
                              node->value_0C);
            if (node->left != 0 && node->left != prev) {
                prev = node;
                node = node->left;
                continue;
            }
            if (node == first)
                break;
            prev = node;
            node = node->parent;
        }
    }
}
