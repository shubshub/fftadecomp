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
    Task *current;
    u16 phase;
} TaskManager;

extern TaskManager *data_02008FF0;
extern void func_080058A4(TaskManager *manager, Task *task);

void func_08005A24(void *context)
{
    TaskManager *manager = context;
    TaskEvent event;
    Task *node;
    Task *removed;

    data_02008FF0 = manager;
    manager->phase ^= 1;
    node = manager->head;
    while (node) {
        if (manager->phase != (node->flags & 1)) {
            event.phase = node->state;
            data_02008FF0->current = node;
            node->callback(node, &event, node + 1);
            node->state = event.phase;
            node->flags ^= 1;
            data_02008FF0->current = 0;
        }
        if (node->state == 3) {
            removed = node;
            if (node->next && manager->phase != (node->next->flags & 1))
                node = node->next;
            else
                node = node->parent;
            func_080058A4(data_02008FF0, removed);
        } else if (node->child && manager->phase != (node->child->flags & 1)) {
            node = node->child;
        } else if (node->next && manager->phase != (node->next->flags & 1)) {
            node = node->next;
        } else {
            node = node->parent;
        }
    }
    data_02008FF0 = 0;
}
