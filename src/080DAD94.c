#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct DrawingDescriptor {
    u32 unknown_00[5];
    u16 x;
    u16 y;
    u16 mode;
} DrawingDescriptor;

u32 func_080D9CF4(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

/* Complete [0x080DAD94, 0x080DADBC): 40 bytes. */
void *func_080DAD94(u16 x, u16 y, u8 mode, void *parent)
{
    DrawingDescriptor descriptor;

    descriptor.x = x;
    descriptor.y = y;
    descriptor.mode = mode;
    return func_08005B6C(func_080D9CF4, 0x14, &descriptor, parent);
}
