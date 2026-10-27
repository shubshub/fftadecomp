#include "ffta.h"

typedef struct ListContext08021A3C ListContext08021A3C;

typedef struct {
    void *allocator;
    ListContext08021A3C *first;
    ListContext08021A3C *second;
    u16 value_0C;
    u16 value_0E;
    u16 value_10;
    u16 value_12;
    u8 unknown_14[0x1CC];
    u16 flags;
    u8 unknown_1E2[6];
} ListOwner08021A3C;

typedef void (*BufferInitializer08021A3C)(void *destination, u32 size);

extern void *func_08007138(void *allocator, u32 size);
extern ListContext08021A3C *func_080C799C(void *allocator);
extern BufferInitializer08021A3C const g_callbacks_0836D4B8[];

/* Complete [0x08021A3C, 0x08021AC4): 136 bytes, 61 instructions. */
ListOwner08021A3C *func_08021A3C(void *allocator, u16 first, u16 second,
                                u16 third, u16 fourth)
{
    ListOwner08021A3C *owner = func_08007138(allocator, sizeof(*owner));

    g_callbacks_0836D4B8[0](owner, sizeof(*owner));
    owner->allocator = allocator;
    owner->first = func_080C799C(owner->allocator);
    owner->second = func_080C799C(owner->allocator);
    owner->value_0C = first;
    owner->value_0E = second;
    owner->value_10 = third;
    owner->value_12 = fourth;
    owner->flags = 3;
    return owner;
}
