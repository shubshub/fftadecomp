/* 0x08006970: 64 target bytes, including the callback literal at 0x080069AC. */
#include "ffta.h"

typedef struct TransitionEvent {
    u16 state;
    u8 unknown_02[0x12];
    u16 initial;
    u16 target;
    s16 duration;
} TransitionEvent;

typedef struct TransitionPayload TransitionPayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_0800664C(void *task, TransitionEvent *event, TransitionPayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_08006970(u8 initial_first, u8 initial_second,
                  u8 target_first, u8 target_second, u16 duration, void *parent)
{
    TransitionEvent descriptor;

    descriptor.initial = (initial_first << 8) | initial_second;
    descriptor.target = (target_first << 8) | target_second;
    descriptor.duration = duration;
    return func_08005B6C((TaskCallback)func_0800664C, 0x38, &descriptor, parent);
}
