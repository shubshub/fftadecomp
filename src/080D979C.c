#include "ffta.h"

typedef struct SchedulerDescriptor080D979C {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u16 third;
} SchedulerDescriptor080D979C;

typedef u32 (*SchedulerCallback080D979C)(void *task, void *descriptor,
                                       void *payload);

u32 func_080D8E00(void *task, SchedulerDescriptor080D979C *descriptor,
                  void *payload);
void *func_08005B6C(SchedulerCallback080D979C callback, u16 payload_size,
                  void *descriptor, void *parent);

/* 0x080D979C: 56 target bytes, including the callback literal.
 * 30b587b00a9d0006000e0906090e1206120e6c46a0826846c182028301930548b621
 * 49006a462b1c2cf7d2f907b030bc02bc0847018e0d08
 */
void *func_080D979C(u8 first, u8 second, u8 third, void *value, void *parent)
{
    SchedulerDescriptor080D979C descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.third = third;
    descriptor.value = value;
    return func_08005B6C((SchedulerCallback080D979C)func_080D8E00,
                         0x16C, &descriptor, parent);
}
