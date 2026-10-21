/* func_080C7D70 - 0x080C7D70, 86 bytes - MATCH
 *
 * In-order walk over a threaded binary tree.  The context holds the root at
 * +0x08; every node links its parent at +0x08, its right child at +0x0C and
 * its left child at +0x10.
 *
 * The walk keeps the node it came from in `previous`, seeded with the
 * sentinel (TreeNode *)-1, and uses it to recognise the links that lead back
 * to the parent.  A node is reported through the callback once both of its
 * children have been handled; the callback's zero return stops the walk.
 */

#include "ffta.h"

typedef struct TreeNode {
    u8 unknown_00[8];
    struct TreeNode *parent;   /* +0x08 */
    struct TreeNode *right;    /* +0x0C */
    struct TreeNode *left;     /* +0x10 */
} TreeNode;

typedef struct {
    u8 unknown_00[8];
    TreeNode *root;            /* +0x08 */
} TreeContext;

typedef int (*TreeCallback)(TreeNode *node, void *payload);

void func_080C7D70(TreeContext *context, TreeCallback callback, void *payload)
{
    TreeNode *current = context->root;
    TreeNode *previous = (TreeNode *)-1;
    TreeNode *root = current;

    while (current != 0) {
        if (current->left != 0 && current->left != previous &&
            current->right != previous) {
            previous = current;
            current = current->left;
            continue;
        }
        if (current->right != previous) {
            if (callback(current, payload) == 0)
                return;
            if (current->right != 0) {
                previous = current;
                current = current->right;
                continue;
            }
        }
        if (current == root)
            return;
        previous = current;
        current = current->parent;
    }
}
