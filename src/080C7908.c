/* func_080C7908 - 0x080C7908, 148 bytes - MATCH
 *
 * Tears a context down: the list it owns is released, the tree it owns is
 * released, the two roots are cleared, and the context itself goes back to
 * the allocation block.  The allocation block is handed back to the caller.
 *
 *   f0b5 4f46 4646 c0b4 051c a946 2f1c 2e68
 *   6c68 002c 09d0 a168 0029 02d0 301c
 *   00f04ffa 301c 211c 3ff71ffc 0020 7860
 *   a846 2f68 ac68 0122 5242 261c 002c 1ad0
 *   e068 2169 0028 06d0 9042 04d0 9142 02d0
 *   221c 041c f2e7 0029 04d0 9142 02d0 221c
 *   0c1c ebe7 381c 211c 3ff7fffb b442 02d0
 *   221c a468 e2e7 0020 4146 8860 4846 0468
 *   201c 291c 3ff7f1fb 201c 18bc 9846 a146
 *   f0bc 02bc 0847
 *
 * The context holds the allocation block at +0x00, the list head at +0x04 and
 * the tree root at +0x08:
 *
 *   +0x00  owner       the allocation block every node comes from
 *   +0x04  head        first node of the list
 *   +0x08  root        root of the tree
 *
 * A list node holds the object at +0x00, the node behind it at +0x04 and the
 * node after it at +0x08, so the whole list is released by handing the tail
 * to func_080C7DC8 and then the head itself to func_08007170.
 *
 * The tree nodes carry a key at +0x00, a value at +0x04, the parent at +0x08,
 * the left child at +0x0C and the right child at +0x10, and func_080C7AB4
 * orders new nodes by the key.  The walk descends into the left child while
 * there is one that is not the node the walk came from, then into the right
 * child, and releases a node once it has no children left; the node the walk
 * came from is remembered in `prev`, seeded with the sentinel
 * (TreeNode *)-1, so that a released subtree is not walked twice.
 *
 * func_08007170 releases one node, func_08007138 allocates one.
 */

#include "ffta.h"

typedef struct ListNode {
    void *value;             /* +0x00 */
    struct ListNode *prev;   /* +0x04 */
    struct ListNode *next;   /* +0x08 */
} ListNode;

typedef struct TreeNode {
    u32 key;                 /* +0x00 */
    u32 value;               /* +0x04 */
    struct TreeNode *parent; /* +0x08 */
    struct TreeNode *left;   /* +0x0C */
    struct TreeNode *right;  /* +0x10 */
    u32 flags;               /* +0x14 */
} TreeNode;

typedef struct {
    void *owner;             /* +0x00 */
    void *head;              /* +0x04 */
    TreeNode *root;          /* +0x08 */
} TreeContext;

void func_080C7DC8(void *owner, ListNode *node);
void func_08007170(void *owner, u8 *object);

void *func_080C7908(TreeContext *context)
{
    TreeContext *release = context;
    TreeContext *list = context;

    {
        void *owner = context->owner;
        ListNode *node = context->head;

        if (node != 0) {
            if (node->next != 0)
                func_080C7DC8(owner, node->next);
            func_08007170(owner, (u8 *)node);
        }
        list->head = 0;
    }
    {
        TreeContext *tree = context;
        void *owner = context->owner;
        TreeNode *node = context->root;
        TreeNode *prev = (TreeNode *)-1;
        TreeNode *root = node;

        if (node != 0) {
            do {
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
                    break;
                prev = node;
                node = node->parent;
            } while (node != 0);
        }
        tree->root = 0;
    }
    {
        void *owner = release->owner;

        func_08007170(owner, (u8 *)context);
        return owner;
    }
}
