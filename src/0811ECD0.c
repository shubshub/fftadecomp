/* 0x0811ECD0: complete 36-byte caller, including the callback literal.
 * 00b587b00b1c0006000e69468882044808216a46e6f642ff07b002bc0847000029eb1108
 */
#include "ffta.h"

typedef struct SchedulerDescriptor0811ECD0 {
    u8 unknown_00[0x14];
    u16 first;
    u8 unknown_16[6];
} SchedulerDescriptor0811ECD0;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_0811EB28(void *task, SchedulerDescriptor0811ECD0 *descriptor,
                  void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_0811ECD0(u8 first, void *parent)
{
    SchedulerDescriptor0811ECD0 descriptor;

    descriptor.first = first;
    return func_08005B6C((TaskCallback)func_0811EB28, 8, &descriptor, parent);
}
