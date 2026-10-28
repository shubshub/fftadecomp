#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u8 unknown_04[0x14];
    const u8 *data;
} Object0800AF8C;

/* 0x0800AF8C - 30-byte target. */
u16 func_0800AF8C(const Object0800AF8C *object)
{
    const u8 *data = object->data;

    return data[0] | (data[1] << 8);
}
