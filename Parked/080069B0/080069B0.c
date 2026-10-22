#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct TransitionDescriptor {
    u32 unknown_00[5];
    u16 initial;
    u16 target;
    u16 duration;
} TransitionDescriptor;

u32 func_0800664C(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080069B0(u8 target_first, u8 target_second,
                  u16 duration, void *parent)
{
    TransitionDescriptor descriptor;
    u8 *output = (u8 *)0x03000940;
    u8 initial_first = output[0x4C];
    u8 initial_second = output[0x4D];

    descriptor.initial = (initial_first << 8) | initial_second;
    descriptor.target = (target_first << 8) | target_second;
    descriptor.duration = duration;
    return func_08005B6C(func_0800664C, 0x38, &descriptor, parent);
}
