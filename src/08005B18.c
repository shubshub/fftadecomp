#include "ffta.h"

typedef struct TaskManagerPrefix {
    void *owner;
    void *head;
} TaskManagerPrefix;

void func_080058A4(void *manager, void *task);

void func_08005B18(void *manager)
{
    TaskManagerPrefix *state = (TaskManagerPrefix *)manager;
    void *head = state->head;

    if (head)
        func_080058A4(manager, head);
}
