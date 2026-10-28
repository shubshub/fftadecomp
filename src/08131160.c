#include "ffta.h"

typedef struct Object Object;

typedef struct {
    const Object *source;
    const Object *target;
} ObjectPair;

extern s32 func_0812F054(const Object *source, const Object *target);

u8 func_08131160(const ObjectPair *context)
{
    return func_0812F054(context->source, context->target);
}
