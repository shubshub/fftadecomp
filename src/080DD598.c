#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 value;
} ObjectState;

/* 080DD598..080DD5A6: 14 bytes. */
u32 func_080DD598(const ObjectState *object)
{
    return object->value != 0;
}
