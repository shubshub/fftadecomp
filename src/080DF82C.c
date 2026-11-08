/* 0x080DF82C: 52 target bytes, including the callback literal.
 * f0b58ab00f9d109e119f07ac079021716271e3802581684686820194044820216a463b1c
 * 26f78cf90ab0f0bc02bc0847fded0d08
 */
#include "ffta.h"

typedef struct TaskParameters080DF82C {
    void *object;
    u8 first;
    u8 second;
    u16 third;

    u16 fourth;
    u8 unknown_0a[2];
} TaskParameters080DF82C;

typedef struct SchedulerDescriptor080DF82C {
    u16 phase;
    u16 unknown_02;
    TaskParameters080DF82C *parameters;
    u8 unknown_08[12];
    u16 value;
    u8 unknown_16[6];
} SchedulerDescriptor080DF82C;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DEDFC(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF82C(void *object, u8 first, u8 second, u16 third, u16 fourth,
                    u16 value, void *parent)
{
    SchedulerDescriptor080DF82C descriptor;
    TaskParameters080DF82C parameters;

    parameters.object = object;
    parameters.first = first;
    parameters.second = second;
    parameters.third = third;
    parameters.fourth = fourth;
    descriptor.value = value;
    descriptor.parameters = &parameters;
    return func_08005B6C(func_080DEDFC, 0x20, &descriptor, parent);
}
