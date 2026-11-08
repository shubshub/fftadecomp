/* 0x080DFD68: 36 target bytes, including the callback literal.
 * 00b587b0131c0006000e6a4690826846c1820348142125f7f5fe07b002bc0847adfc0d08
 */
#include "ffta.h"

typedef struct FadeDescriptor080DFD68 {
    u16 phase;
    u8 unknown_02[0x12];
    u16 direction;
    s16 duration;
    u8 unknown_18[4];
} FadeDescriptor080DFD68;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DFCAC(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DFD68(u8 direction, s16 duration, void *parent)
{
    FadeDescriptor080DFD68 descriptor;

    descriptor.direction = direction;
    descriptor.duration = duration;
    return func_08005B6C(func_080DFCAC, 0x14, &descriptor, parent);
}
