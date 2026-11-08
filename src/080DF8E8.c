#include "ffta.h"

/* 0x080DF8E8: 36 target bytes, including the callback literal.
 * 00b587b00906090e019068468282c182034814216a4626f735f907b002bc08471de60d08
 */
typedef struct SchedulerDescriptor080DF8E8 {
    u16 state;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[0x0c];
    u16 first;
    u16 second;
    u16 third;
} SchedulerDescriptor080DF8E8;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DE61C(void *task, SchedulerDescriptor080DF8E8 *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF8E8(void *value, u8 second, u32 first, void *parent)
{
    SchedulerDescriptor080DF8E8 descriptor;

    descriptor.value = value;
    descriptor.first = first;
    descriptor.second = second;
    return func_08005B6C((TaskCallback)func_080DE61C, 0x14, &descriptor, parent);
}
