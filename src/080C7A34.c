struct Node {
    void *owner;
    struct Node *previous;
    struct Node *next;
};

struct List {
    void *allocator;
    struct Node *head;
};

extern void func_08007170(void *allocator, void *object);

/* Target: 080C7A34..080C7A5C, 40 bytes. */
void func_080C7A34(struct List *list, struct Node *node)
{
    struct Node *previous = node->previous;

    if (previous == 0)
        list->head = node->next;
    else
        previous->next = node->next;

    if (node->next != 0)
        node->next->previous = node->previous;

    func_08007170(list->allocator, node);
}
