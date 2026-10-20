#include "ffta.h"

typedef struct {
    u8 unknown_00[0xA];
    u16 position;
    u16 index;
    u8 unknown_0E[0x26];
    u8 *table;
    u8 *current;
} Resource;

void func_08021E28(void *data, u32 index)
{
    Resource *resource = data;

    resource->index = index;
    resource->position = 0;
    resource->current = resource->table + index * 20;
}
