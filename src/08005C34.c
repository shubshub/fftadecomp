#include "ffta.h"

typedef struct {
    void *owner;
} TaskManager;

void func_08007170(void *owner, u8 *object);
void func_0800718C(void *object);

void func_08005C34(void *manager)
{
    void *owner = ((TaskManager *)manager)->owner;

    func_08007170(owner, manager);
    func_0800718C(owner);
}
