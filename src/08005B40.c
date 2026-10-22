#include "ffta.h"

typedef struct TaskManagerOwner {
    void *owner;
} TaskManagerOwner;

void func_08007170(void *owner, u8 *object);

void func_08005B40(void *object)
{
    TaskManagerOwner **manager = (TaskManagerOwner **)0x02008FF0;

    func_08007170((*manager)->owner, object);
}
