#include "ffta.h"

// Complete [0x080C7C48, 0x080C7CC0): 120 bytes, including two callback literals.
// 70b581b0041c251c004e1fe0797e0c08201cfff7fdfd009a5069012108435061a868002801d1
// aa6010e0011c13680868834204dac868002804d1ca6005e00869002801d0011cf2e70a619160
// 00200090201c311c6a4600f067f800990029d7d10449201c002200f05ff801b070bc01bc0047
// 0000957e0c08

typedef struct TreeNode080C7C48 {
    s32 key;
    void *value;
    struct TreeNode080C7C48 *parent;
    struct TreeNode080C7C48 *left;
    struct TreeNode080C7C48 *right;
    u32 flags;
} TreeNode080C7C48;

typedef struct {
    void *owner;
    void *head;
    TreeNode080C7C48 *root;
} TreeContext080C7C48;

typedef int (*TreeCallback080C7C48)(TreeNode080C7C48 *, void *);

extern void func_080C7858(TreeContext080C7C48 *, TreeNode080C7C48 *);
extern void func_080C7D70(TreeContext080C7C48 *, TreeCallback080C7C48, void *);
extern int func_080C7E78(TreeNode080C7C48 *, TreeNode080C7C48 **);
extern int func_080C7E94(TreeNode080C7C48 *);

// Re-sorts every node whose flag bit 0 is clear: each one found is unlinked,
// marked and inserted again by key, then the marks are cleared.
void func_080C7C48(TreeContext080C7C48 *context)
{
    TreeContext080C7C48 *tree = context;
    TreeNode080C7C48 *node;
    TreeNode080C7C48 *cur;
    s32 key;

    while (node = 0, func_080C7D70(context, (TreeCallback080C7C48)func_080C7E78, &node), node != 0) {
        func_080C7858(context, node);
        node->flags |= 1;
        if (tree->root == 0) {
            tree->root = node;
            continue;
        }
        cur = tree->root;
        key = node->key;
        while (1) {
            if (key < cur->key) {
                if (cur->left != 0) {
                    cur = cur->left;
                    continue;
                }
                cur->left = node;
                node->parent = cur;
            } else {
                if (cur->right != 0) {
                    cur = cur->right;
                    continue;
                }
                cur->right = node;
                node->parent = cur;
            }
            break;
        }
    }
    func_080C7D70(context, (TreeCallback080C7C48)func_080C7E94, 0);
}
