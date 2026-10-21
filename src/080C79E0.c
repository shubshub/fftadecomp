/* func_080C79E0 - 0x080C79E0, 82 bytes - MATCH
 *
 * Empties the tree the context owns: every node is released back to the
 * allocation block and the root pointer is cleared.
 *
 *   f0b5 051c 2f68 ac68 0122 5242 261c 002c
 *   1ad0 e068 2169 0028 06d0 9042 04d0 9142
 *   02d0 221c 041c f2e7 0029 04d0 9142 02d0
 *   221c 0c1c ebe7 381c 211c 3ff7a9fb b442 02d0
 *   221c a468 e2e7 0020 a860 f0bc 01bc 0047
 *
 * The nodes form a binary tree with parent links (func_080C7AB4 inserts into
 * it and keeps the parent of every node):
 *
 *   +0x00  key         (func_080C7AB4 orders new nodes by it)
 *   +0x04  value
 *   +0x08  parent
 *   +0x0C  left child
 *   +0x10  right child
 *   +0x14  flags
 *
 * The context keeps the allocation block at +0x00, the list head at +0x04
 * (func_080C7A74 appends to that list) and the tree root at +0x08.
 *
 * The walk descends into the left child while there is one that is not the
 * node the walk came from, then into the right child, and releases a node
 * once it has no children left.  Climbing back up leaves the released child
 * still linked into its parent, so the node the walk came from is remembered
 * and never entered a second time - that is what keeps a subtree from being
 * walked again after it has been emptied.
 *
 * func_08007170 releases one node; func_08007138 allocates one.
 */

#include "ffta.h"

void func_08007170(void *owner, u8 *object);

typedef struct TreeNode {
    u32 key;                    /* +0x00 */
    u32 value;                  /* +0x04 */
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

void func_080C79E0(TreeContext *context)
{
    void *owner = context->owner;
    TreeNode *node = context->root;
    TreeNode *prev = (TreeNode *)-1;
    TreeNode *root = node;

    while (node != 0) {
        TreeNode *left = node->left;
        TreeNode *right = node->right;

        if (left != 0 && left != prev && right != prev) {
            prev = node;
            node = left;
            continue;
        }
        if (right != 0 && right != prev) {
            prev = node;
            node = right;
            continue;
        }
        func_08007170(owner, (u8 *)node);
        if (node == root)
            goto done;
        prev = node;
        node = node->parent;
    }
done:
    context->root = 0;
}
