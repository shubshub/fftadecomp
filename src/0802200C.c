#include "ffta.h"

typedef struct {
    void *allocator;
} AllocationOwner;

typedef struct {
    u8 unknown_00[4];
    void *allocation;
    u8 unknown_08[0x10];
    AllocationOwner *owner;
} AllocationState;

extern void func_08007170(void *allocator, void *allocation);

/* 0802200C..0802202A: 30 bytes, 13 instructions. */
void func_0802200C(AllocationState *object)
{
    func_08007170(object->owner->allocator, object->allocation);
    func_08007170(object->owner->allocator, object);
}
