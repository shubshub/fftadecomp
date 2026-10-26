#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    void *collection;
} CollectionOwner;

void *func_080C7B08(void *collection);

void *func_08099CC4(CollectionOwner *owner)
{
    return func_080C7B08(owner->collection);
}
