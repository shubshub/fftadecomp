#include "ffta.h"

typedef struct TaskManagerPrefix {
    void *owner;
} TaskManagerPrefix;

void func_08007170(void *owner, u8 *allocation);

/* 0x08005B0C-0x08005B18: 12 bytes. */
void func_08005B0C(TaskManagerPrefix *manager, u8 *allocation)
{
    func_08007170(manager->owner, allocation);
}
