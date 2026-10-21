/* func_080C7AB4 - 0x080C7AB4, 84 bytes
 *
 * Inserts a new node into the tree the context owns, ordered by the key.
 * A key that is not smaller than the key of the node it is compared with
 * goes right, a smaller one goes left.
 *
 *   70b5 051c 0c1c 161c 2868 1821 3ff7 3afb 031c
 *   5c60 1e60 0020 9860 d860 1861 5861 a868 0028
 *   01d1 ab60 10e0 011c 321c 0868 8242 04da c868
 *   0028 04d1 cb60 05e0 0869 0028 01d0 011c f2e7
 *   0b61 9960 181c 70bc 02bc 0847
 *
 * The node is 24 bytes and comes from the allocation block the context holds
 * at +0x00:
 *
 *   +0x00  key
 *   +0x04  value
 *   +0x08  parent
 *   +0x0C  left child
 *   +0x10  right child
 *   +0x14  flags
 *
 * The context keeps the allocation block at +0x00, the list head at +0x04
 * (func_080C7A74 appends to that list) and the tree root at +0x08.  An empty
 * tree takes the new node as its root and leaves it parentless; a populated
 * one is walked down until a free child slot turns up, and the node the walk
 * came from becomes the parent of the new node.
 *
 * The walk is the same one func_080C79E0 tears down again: it descends into
 * the left child while there is one and into the right child otherwise, and
 * stops at the first node with a free child on the side the key points at.
 *
 * func_08007138 allocates one node; the callers hand in the value to store
 * and the key to order it by.
 */

#include "ffta.h"

void *func_08007138(void *owner, u32 size);

typedef struct TreeNode {
    s32 key;                    /* +0x00 */
    void *value;                /* +0x04 */
    struct TreeNode *parent;    /* +0x08 */
    struct TreeNode *left;      /* +0x0C */
    struct TreeNode *right;     /* +0x10 */
    u32 flags;                  /* +0x14 */
} TreeNode;

typedef struct {
    void *owner;                 /* +0x00 */
    void *head;                  /* +0x04 */
    TreeNode *root;              /* +0x08 */
} TreeContext;

TreeNode *func_080C7AB4(TreeContext *context, void *value, s32 key)
{
    TreeNode *node = func_08007138(context->owner, 24);

    node->value = value;
    node->key = key;
    node->parent = 0;
    node->left = 0;
    node->right = 0;
    node->flags = 0;

    if (context->root == 0) {
        context->root = node;
    } else {
        TreeNode *cur = context->root;
        s32 k = key;

        while (1) {
            if (k < cur->key) {
                if (cur->left != 0) {
                    cur = cur->left;
                    continue;
                }
                cur->left = node;
            } else {
                if (cur->right != 0) {
                    cur = cur->right;
                    continue;
                }
                cur->right = node;
            }
            break;
        }
        node->parent = cur;
    }
    return node;
}
