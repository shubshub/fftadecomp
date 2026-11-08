/* 0x080D98D4: complete 64-byte caller, including the callback literal.
 * 70b589b00d9d0e9e0006000e12046c46a0826846c1821b04120c1a43079207a8456001900548
 * a82149006a46331c2cf733f909b070bc02bc0847000051930d08
 */
#include "ffta.h"

typedef struct Parameters080D98D4 {
    u16 low;
    u16 high;
    void *value;
} Parameters080D98D4;

typedef struct SchedulerDescriptor080D98D4 {
    u8 unknown_00[4];
    Parameters080D98D4 *args;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} SchedulerDescriptor080D98D4;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D9350(void *task, SchedulerDescriptor080D98D4 *descriptor,
                  void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D98D4(u8 first, u16 second, u16 low, u16 high, void *value,
                    void *parent)
{
    SchedulerDescriptor080D98D4 descriptor;
    Parameters080D98D4 args;

    descriptor.first = first;
    descriptor.second = second;
    args.low = low;
    args.high = high;
    args.value = value;
    descriptor.args = &args;
    return func_08005B6C((TaskCallback)func_080D9350, 0x150, &descriptor,
                         parent);
}
