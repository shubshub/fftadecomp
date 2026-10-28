#include "ffta.h"

/* 080C7D18 .. 080C7D6E: 86 bytes. */
typedef struct TreeNode TreeNode;
struct TreeNode {
    u8 unknown_00[8];
    TreeNode *parent;
    TreeNode *child;
    TreeNode *next;
};

typedef struct {
    u8 unknown_00[8];
    TreeNode *root;
} Tree;

void func_080C7D18(Tree *tree, s32 (*callback)(TreeNode *, void *), void *context)
{
    TreeNode *node = tree->root;
    TreeNode *previous = (TreeNode *)-1;
    TreeNode *root = node;

    while (node) {
        TreeNode *child = node->child;
        if (child && child != previous) {
            if (node->next != previous) {
                previous = node;
                node = child;
                continue;
            }
        } else if (node->next != previous) {
            if (!callback(node, context))
                return;
            if (node->next) {
                previous = node;
                node = node->next;
                continue;
            }
        }
        if (node == root)
            return;
        previous = node;
        node = node->parent;
    }
}
