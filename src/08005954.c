#include "ffta.h"

typedef struct Task Task;
typedef struct {
    u16 phase;
    u16 argument;
    u32 data[6];
} TaskEvent;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);
typedef void (*BufferInitializer)(void *destination, u32 size);

struct Task {
    TaskCallback callback;
    Task *previous;
    Task *next;
    Task *parent;
    Task *child;
    u16 state;
    u16 flags;
    /* The allocation includes this first word before the requested payload bytes. */
    u32 payload[1];
};

typedef struct {
    void *heap;
    Task *head;
    Task *current;
    u16 flags;
} TaskManager;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_08007138(void *heap, u32 bytes);

static inline Task *last_sibling(Task *task)
{
    while (task->next)
        task = task->next;
    return task;
}

void *func_08005954(void *manager, TaskCallback callback, u16 payload_size,
                    void *descriptor, void *parent_task)
{
    TaskManager *tasks;
    TaskEvent event;
    Task *task;
    Task *last;
    Task *parent;

    payload_size += sizeof(*task);
    task = func_08007138(((TaskManager *)manager)->heap, payload_size);
    g_callbacks_0836D4B8[0](task, payload_size);
    task->callback = callback;
    tasks = manager;
    task->flags = tasks->flags;
    parent = parent_task;
    if (parent) {
        if (parent->child) {
            last = last_sibling(parent->child);
            last->next = task;
            task->previous = last;
        } else {
            parent->child = task;
        }
        task->parent = parent;
    } else if (!tasks->head) {
        tasks->head = task;
    } else {
        last = last_sibling(tasks->head);
        last->next = task;
        task->previous = last;
    }
    event = *(const TaskEvent *)descriptor;
    event.phase = 0;
    task->callback(task, &event, task->payload);
    task->state = 0x100;
    return task;
}
