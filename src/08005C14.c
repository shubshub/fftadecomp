#include "ffta.h"

typedef struct {
    void *owner;
    void *head;
    void *current;
    u16 phase;
} TaskManager;

u8 *func_080070C8(u8 *storage, u32 byte_count);
void *func_08007138(void *owner, u32 byte_count);

void *func_08005C14(void *storage, u32 byte_count)
{
    void *owner = func_080070C8(storage, byte_count);
    TaskManager *manager = func_08007138(owner, sizeof(*manager));

    manager->owner = owner;
    manager->head = 0;
    manager->current = 0;
    manager->phase = 0;
    return manager;
}
