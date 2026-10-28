#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    void *first_context;
    void *second_context;
} Owner08099790;

typedef struct {
    u8 unknown_00[0x24];
    s32 key;
    u8 unknown_28[0x58];
    Owner08099790 *owner;
} Object08099790;

extern void *func_080C7BF4(void *context, u32 key);
extern void *func_080C7A74(void *context, void *value);
extern void *func_080C7AB4(void *context, void *value, s32 key);

/* 0x08099790..0x080997E6: 86 bytes, 37 instructions. */
void func_08099790(Object08099790 *object)
{
    if (!func_080C7BF4(object->owner->first_context, (u32)object)) {
        func_080C7A74(object->owner->first_context, object);
        func_080C7AB4(object->owner->first_context, object, object->key);
    }
    if (!func_080C7BF4(object->owner->second_context, (u32)object)) {
        func_080C7A74(object->owner->second_context, object);
        func_080C7AB4(object->owner->second_context, object, object->key);
    }
}
