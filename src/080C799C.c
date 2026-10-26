struct Node {
    void *owner;
    struct Node *previous;
    struct Node *next;
};

extern void *func_08007138(void *owner, unsigned int size);

/* Target: 080C799C..080C79B4, 24 bytes. */
struct Node *func_080C799C(void *owner)
{
    struct Node *node = func_08007138(owner, sizeof(*node));

    node->owner = owner;
    node->previous = 0;
    node->next = 0;
    return node;
}
