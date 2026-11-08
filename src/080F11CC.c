/* 0x080F11CC: complete 36-byte caller, including the callback literal.
 * 00b587b0131c0906090e6a46918201900348302114f7c4fc07b002bc08470000f50e0f08
 */
#include "ffta.h"

typedef struct SchedulerDescriptor080F11CC {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[12];
    u16 first;
    u8 unknown_16[6];
} SchedulerDescriptor080F11CC;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080F0EF4(void *task, SchedulerDescriptor080F11CC *descriptor,
                  void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080F11CC(void *value, u8 first, void *parent)
{
    SchedulerDescriptor080F11CC descriptor;

    descriptor.first = first;
    descriptor.value = value;
    return func_08005B6C((TaskCallback)func_080F0EF4, 0x30, &descriptor, parent);
}
