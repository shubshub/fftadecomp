#include "ffta.h"

/* 0x080DF90C: 32 target bytes, including the callback literal.
 * 00b587b0131c019068468182034830216a4626f725f907b002bc084719e80d08
 */
typedef struct SchedulerDescriptor080DF90C {
    u16 state;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[0x0c];
    u16 first;
    u16 unknown_16;
    u8 unknown_18[4];
} SchedulerDescriptor080DF90C;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DE818(void *task, SchedulerDescriptor080DF90C *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF90C(void *value, u32 first, void *parent)
{
    SchedulerDescriptor080DF90C descriptor;

    descriptor.value = value;
    descriptor.first = first;
    return func_08005B6C((TaskCallback)func_080DE818, 0x30, &descriptor, parent);
}
