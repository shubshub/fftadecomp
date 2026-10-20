#include "ffta.h"

typedef struct PriorityNode {
    void *object;
    s16 priority;
    u16 value_06;
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

u32 func_08149368(const void *object);

void func_08148860(void *object, s32 priority, u32 value_08, u32 value_0C)
{
    PriorityTree *tree;
    PriorityNode *node;
    PriorityNode *current;

    if (priority <= 0)
        return;
    tree = &g_state_03005F30;
    if (tree->count > 15)
        return;
    if (func_08149368(object) == 1)
        return;

    node = &tree->nodes[tree->count];
    tree->count++;
    if (tree->value_1C8 > priority)
        tree->value_1C8 = priority;
    if (tree->value_1C4 > priority)
        tree->value_1C4 = priority;
    node->object = object;
    node->priority = priority;
    node->left = 0;
    node->right = 0;
    node->parent = 0;
    node->value_06 = 0;
    node->value_08 = value_08;
    node->value_0C = value_0C;

    if (tree->root == 0) {
        tree->root = node;
    } else {
        s32 comparisonPriority;

        current = tree->root;
        comparisonPriority = (s16)priority;
        for (;;) {
            if (current->priority >= comparisonPriority) {
                if (current->left != 0) {
                    current = current->left;
                } else {
                    current->left = node;
                    break;
                }
            } else {
                if (current->right != 0) {
                    current = current->right;
                } else {
                    current->right = node;
                    break;
                }
            }
        }
        node->parent = current;
    }
}
