#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    void *collection;
} Owner0809975C;

typedef struct {
    u8 unknown_00[0x24];
    s32 key;
    u8 unknown_28[0x58];
    Owner0809975C *owner;
} Object0809975C;

extern void *func_080C7BF4(void *context, u32 key);
extern void *func_080C7A74(void *context, void *value);
extern void *func_080C7AB4(void *context, void *value, s32 key);

/* Complete [0x0809975C, 0x0809978E): 50 bytes, 22 instructions. */
void func_0809975C(Object0809975C *object)
{
    if (!func_080C7BF4(object->owner->collection, (u32)object)) {
        func_080C7A74(object->owner->collection, object);
        func_080C7AB4(object->owner->collection, object, object->key);
    }
}
