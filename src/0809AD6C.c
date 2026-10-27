#include "ffta.h"

typedef struct {
    u8 unknown_00[0x5C];
    s16 counter;
} CounterObject;

/* 0809AD6C..0809AD92: 38 bytes. */
u32 func_0809AD6C(CounterObject *object, const CounterObject *excluded)
{
    if (object != excluded && object->counter >= 0) {
        if (object->counter > 97)
            object->counter = 98;
        object->counter++;
    }
    return 1;
}
