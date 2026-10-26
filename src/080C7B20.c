typedef unsigned char u8;

struct Node {
    u8 unknown_00[8];
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct Tree {
    u8 unknown_00[8];
    struct Node *root;
};

static inline int count_nodes(struct Node *current)
{
    struct Node *root;
    struct Node *previous;
    int count;

    count = 0;
    previous = (struct Node *)-1;
    root = current;

    while (current != 0) {
        struct Node *right = current->right;

        if (right != 0 && right != previous) {
            if (current->left != previous) {
                previous = current;
                current = right;
                continue;
            }
        } else {
            struct Node *left = current->left;

            if (left != previous) {
                count++;
                if (left != 0) {
                    previous = current;
                    current = left;
                    continue;
                }
            }
        }

        if (current == root)
            break;
        previous = current;
        current = current->parent;
    }

    return count;
}

/* Target: 080C7B20..080C7B74, 84 bytes. */
int func_080C7B20(struct Tree *tree)
{
    struct Node *root = tree->root;

    if (root == 0)
        return 0;
    return count_nodes(root);
}
