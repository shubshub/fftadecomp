#include "ffta.h"

/* Complete 08021F18..08021FB2, including the callback pointer. */
typedef struct Node08021F18 Node08021F18;
struct Node08021F18 {
    unsigned char unknown_00[0x3c];
    Node08021F18 *left;
    Node08021F18 *right;
    Node08021F18 *parent;
};
typedef struct {
    unsigned char unknown_00[0x0c];
    Node08021F18 *root;
} Tree08021F18;

static inline void traverse_tree(Tree08021F18 *tree,
                                 void (*callback)(Node08021F18 *, void *), void *argument)
{
    Node08021F18 *root = tree->root;
    Node08021F18 *node;
    Node08021F18 *first;
    Node08021F18 *previous;

    if (root != 0) {
        node = root;
        first = node;
        previous = (Node08021F18 *)-1;
        do {
            if (node->right != 0 && node->right != previous) {
                if (node->left != previous) {
                    previous = node;
                    node = node->right;
                    continue;
                }
            } else if (node->left != previous) {
                callback(node, argument);
                if (node->left != 0) {
                    previous = node;
                    node = node->left;
                    continue;
                }
            }
            if (node == first)
                return;
            previous = node;
            node = node->parent;
        } while (node != 0);
    }
}

typedef struct {
    s16 x;
    s16 y;
    u8 variant;
    u8 flip_x; /* The original leaves this byte unwritten. */
    u8 flip_y;
    u8 flag_7;
    u8 flag_8;
    u8 offset_9;
    u8 mode;
} DrawArguments;

extern void func_080216F8(Node08021F18 *node, void *argument);

void func_08021F18(Tree08021F18 *tree, s32 x, s32 y, u8 variant, u8 unused,
                   u8 flip_y, u8 flag_7, u8 flag_8, u8 offset_9, u8 mode)
{
    DrawArguments arguments;

    arguments.x = x;
    arguments.y = y;
    arguments.variant = variant;
    arguments.flip_y = flip_y;
    arguments.flag_7 = flag_7;
    arguments.flag_8 = flag_8;
    arguments.offset_9 = offset_9;
    arguments.mode = mode;
    traverse_tree(tree, func_080216F8, &arguments);
}
