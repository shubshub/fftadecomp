#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 status_01;
    u8 unknown_02[4];
    s16 value_06;
} Object0800C084;

/* 0x0800C084-0x0800C09C: 24 bytes. */
s32 func_0800C084(Object0800C084 *object)
{
    if (object->status_01 == 1)
        return -1;

    return object->value_06;
}
