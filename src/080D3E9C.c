/* 0x080D3E9C: 36 target bytes, including the callback literal. */
#include "ffta.h"

typedef struct SequenceEvent {
    u16 state;
    u8 unknown_02[2];
    const void *sequence;
    u8 unknown_08[0x0c];
    u16 flags;
    u16 delay;
    u8 unknown_18[4];
} SequenceEvent;

typedef struct SequencePayload SequencePayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D3CB4(void *task, SequenceEvent *event, SequencePayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D3E9C(const void *sequence, void *parent)
{
    SequenceEvent descriptor;

    descriptor.flags = 0;
    descriptor.delay = 0;
    descriptor.sequence = sequence;
    return func_08005B6C((TaskCallback)func_080D3CB4, 0x2c, &descriptor, parent);
}
