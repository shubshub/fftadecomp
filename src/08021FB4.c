/* 0x08021FB4: 86 target bytes.
 * Traverse the linked nodes using both child links and the parent link. */
typedef struct Node08021FB4 Node08021FB4;
struct Node08021FB4 {
    unsigned char unknown_00[0x3c];
    Node08021FB4 *left;
    Node08021FB4 *right;
    Node08021FB4 *parent;
};
typedef struct {
    unsigned char unknown_00[0x0c];
    Node08021FB4 *root;
} Tree08021FB4;

void func_08021FB4(Tree08021FB4 *tree,
                  void (*callback)(Node08021FB4 *, void *), void *argument)
{
    Node08021FB4 *root = tree->root;
    Node08021FB4 *node;
    Node08021FB4 *first;
    Node08021FB4 *previous;

    if (root != 0) {
        node = root;
        first = node;
        previous = (Node08021FB4 *)-1;
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
