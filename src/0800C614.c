#include "ffta.h"

/* 0x0800C614..0x0800C628: 20 bytes / 10 instructions. */
struct Object0800C614 {
    u8 unknown_00[0x10];
    u16 active;
    void *data;
};

void *func_0800C614(const struct Object0800C614 *object)
{
    u16 active = object->active;
    void *data = 0;

    if (active != 0)
        data = object->data;
    return data;
}
