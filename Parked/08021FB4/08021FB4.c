#include "ffta.h"

typedef struct TreeNode {
    u8 unknown_00[0x3C];
    struct TreeNode *right;
    struct TreeNode *left;
    struct TreeNode *parent;
} TreeNode;

typedef struct {
    u8 unknown_00[0x0C];
    TreeNode *root;
} TreeContext;

typedef void (*TreeCallback)(TreeNode *node, void *payload);

void func_08021FB4(TreeContext *context, TreeCallback callback, void *payload)
{
    TreeNode *current;
    TreeNode *root;
    TreeNode *previous;

    if (context->root != 0) {
        current = context->root;
        root = current;
        previous = (TreeNode *)-1;

        while (current != 0) {
            if (current->left != 0 && current->left != previous &&
                current->right != previous) {
                previous = current;
                current = current->left;
                continue;
            }
            if (current->right != previous) {
                callback(current, payload);
                if (current->right != 0) {
                    previous = current;
                    current = current->right;
                    continue;
                }
            }
            if (current == root)
                break;
            previous = current;
            current = current->parent;
        }
    }
}
