/* 0x080DFD8C: complete 76-byte caller, including the callback literal.
 * 10b58ab01204140c1b041b0c07aa11700021538051709480906008202040002801d00120
 * 04e010202040002801d0022050700192044810216a460c9b25f7d0fe0ab010bc02bc0847
 * 0dfb0d08
 */
#include "ffta.h"

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct {
    u8 count;
    u8 channel;
    u16 delay;
    u16 flags;
    u16 unknown_06;
    const SequenceEvent *events;
} SequenceParameters;

typedef struct {
    u16 phase;
    u16 unknown_02;
    SequenceParameters *parameters;
    u8 unknown_08[0x14];
} SequenceDescriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DFB0C(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DFD8C(const SequenceEvent *events, u8 count, u16 flags,
                    u16 delay, void *parent)
{
    SequenceDescriptor descriptor;
    SequenceParameters parameters;

    parameters.count = count;
    parameters.delay = delay;
    parameters.channel = 0;
    parameters.flags = flags;
    parameters.events = events;
    if (flags & 8)
        parameters.channel = 1;
    else if (flags & 0x10)
        parameters.channel = 2;
    descriptor.parameters = &parameters;
    return func_08005B6C(func_080DFB0C, 0x10, &descriptor, parent);
}
