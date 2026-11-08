#include "ffta.h"

/* 0x080D9B18: 32 target bytes, including the callback literal.
 * 00b587b0131c6a4690820191034810212cf720f807b002bc08470000cd9b0d08
 */
typedef struct SchedulerDescriptor080D9B18 {
    u16 state;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[0x0c];
    u16 first;
    u16 unknown_16;
    u8 unknown_18[4];
} SchedulerDescriptor080D9B18;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D9BCC(void *task, SchedulerDescriptor080D9B18 *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D9B18(u32 first, void *value, void *parent)
{
    SchedulerDescriptor080D9B18 descriptor;

    descriptor.first = first;
    descriptor.value = value;
    return func_08005B6C((TaskCallback)func_080D9BCC, 0x10, &descriptor, parent);
}
