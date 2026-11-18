#include "ffta.h"

typedef struct Task Task;

typedef struct {
    u16 phase;
    u16 argument;
    u32 data[6];
} TaskEvent;

typedef u32 (*TaskCallback)(Task *, TaskEvent *, void *);

struct Task {
    TaskCallback callback;
    Task *previous;
    Task *next;
    Task *parent;
    Task *child;
    u16 state;
    u16 flags;
};

typedef struct {
    void *heap;
    Task *head;
} TaskManager;

extern void func_08007170(void *heap, u8 *allocation);

/* Siblings take precedence, so the last sibling's children are visited first. */
static inline Task *last_leaf(Task *child)
{
    if (child) {
        for (;;) {
            if (child->next)
                child = child->next;
            else if (child->child)
                child = child->child;
            else
                break;
        }
    }
    return child;
}

void func_080058A4(TaskManager *manager, Task *root)
{
    TaskEvent event;
    Task *current;
    Task *node;
    int delay;

    event.phase = 1;
    current = root;
    while (current) {
        node = last_leaf(current->child);
        if (!node)
            node = current;

        node->callback(node, &event, node + 1);
        if (node == root)
            current = 0;
        else if (node->previous)
            current = node->previous;
        else
            current = node->parent;

        if (node->previous)
            node->previous->next = node->next;
        if (node->next)
            node->next->previous = node->previous;
        if (node->parent && node->parent->child == node)
            node->parent->child = node->next;
        if (manager->head == node)
            manager->head = node->next;

        node->parent = 0;
        node->next = 0;
        node->previous = 0;
        /* The original delays four iterations when freeing this heap address. */
        if ((u32)node == 0x0202BA50) {
            for (delay = 0; delay < 4; delay++)
                ;
        }
        func_08007170(manager->heap, (u8 *)node);
    }
}
