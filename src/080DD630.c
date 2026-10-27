#include "ffta.h"

struct ChildContext;

typedef struct {
    u32 unknown_00;
    struct ChildContext *child;
} ObjectState;

extern void func_0809D8D0(struct ChildContext *context, u8 enabled);

static inline u8 has_child(const ObjectState *object)
{
    return object->child != 0;
}

/* 080DD630..080DD650: 32 bytes. */
void func_080DD630(ObjectState *object, u8 enabled)
{
    if (has_child(object))
        func_0809D8D0(object->child, enabled);
}
