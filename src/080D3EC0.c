#include "ffta.h"

typedef struct Sequence Sequence;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct SequenceDescriptor {
    u16 phase;
    u8 unknown_02[2];
    const Sequence *sequence;
    u8 unknown_08[12];
    u16 flags;
    u16 delay;
    u8 unknown_18[4];
} SequenceDescriptor;

u32 func_080D3CB4(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

/* Complete [0x080D3EC0, 0x080D3EE8): 40 bytes. */
void *func_080D3EC0(const Sequence *sequence, u16 delay, void *parent)
{
    SequenceDescriptor descriptor;

    descriptor.flags = 0;
    descriptor.delay = delay;
    descriptor.sequence = sequence;
    return func_08005B6C(func_080D3CB4, 0x2C, &descriptor, parent);
}
