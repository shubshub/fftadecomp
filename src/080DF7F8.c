/* 0x080DF7F8: 52 target bytes, including the callback literal.
 * f0b58ab00f9d109e119f07ac079021716271a3712581684686820194044818216a463b1c
 * 26f7a6f90ab0f0bc02bc084785ec0d08
 */
#include "ffta.h"

typedef struct TaskParameters080DF7F8 {
    void *object;
    u8 first;
    u8 second;
    u8 third;
    u8 unknown_07;
    u16 fourth;
    u8 unknown_0a[2];
} TaskParameters080DF7F8;

typedef struct SchedulerDescriptor080DF7F8 {
    u16 phase;
    u16 unknown_02;
    TaskParameters080DF7F8 *parameters;
    u8 unknown_08[12];
    u16 value;
    u8 unknown_16[6];
} SchedulerDescriptor080DF7F8;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DEC84(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF7F8(void *object, u8 first, u8 second, u8 third, u16 fourth,
                    u16 value, void *parent)
{
    SchedulerDescriptor080DF7F8 descriptor;
    TaskParameters080DF7F8 parameters;

    parameters.object = object;
    parameters.first = first;
    parameters.second = second;
    parameters.third = third;
    parameters.fourth = fourth;
    descriptor.value = value;
    descriptor.parameters = &parameters;
    return func_08005B6C(func_080DEC84, 0x18, &descriptor, parent);
}
