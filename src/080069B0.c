#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct TransitionDescriptor {
    u32 unknown_00[5];
    u16 initial;
    u16 target;
    u16 duration;
} TransitionDescriptor;

extern u8 g_control_flags_03000940[];
u32 func_0800664C(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

/* Complete [0x080069B0,0x080069F4): 68 bytes. Other request bytes remain unspecified. */
void *func_080069B0(u8 target_first, u8 target_second,
                  u16 duration, void *parent)
{
    TransitionDescriptor descriptor;
    TransitionDescriptor *request = &descriptor;
    u32 output = (u32)g_control_flags_03000940;
    u16 initial = *(u8 *)(output + 0x4C) << 8;
    initial |= *(u8 *)(output + 0x4D);

    request->initial = initial;
    descriptor.target = (target_first << 8) | target_second;
    descriptor.duration = duration;
    return func_08005B6C(func_0800664C, 0x38, &descriptor, parent);
}
