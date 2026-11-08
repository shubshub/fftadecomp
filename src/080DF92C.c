/* 0x080DF92C: 36 target bytes, including the callback literal.
 * 00b587b00906090e019068468282c182034810216a4626f713f907b002bc084719e90d08
 */
#include "ffta.h"

typedef struct SchedulerDescriptor080DF92C {
    u16 phase;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} SchedulerDescriptor080DF92C;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DE918(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF92C(void *value, u8 second, u16 first, void *parent)
{
    SchedulerDescriptor080DF92C descriptor;

    descriptor.value = value;
    descriptor.first = first;
    descriptor.second = second;
    return func_08005B6C(func_080DE918, 0x10, &descriptor, parent);
}
