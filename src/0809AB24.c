#include "ffta.h"

typedef struct {
    void *value;
} ValueObject;

typedef struct {
    void *owner;
} OwnerContext;

extern void *func_080C7B74(const ValueObject *object);
extern void func_08007170(void *owner, u8 *object);

/* 0x0809AB24..0x0809AB3C: 24 bytes. */
s32 func_0809AB24(const ValueObject *object, const OwnerContext *context)
{
    u8 *value = func_080C7B74(object);

    func_08007170(context->owner, value);
    return 1;
}
