/* 0x080DF75C: 52 target bytes, including the callback literal.
 * f0b58bb0109d119e129f07ac0790616022816381257301946846868204486c216a463b1c
 * 26f7f4f90bb0f0bc02bc0847e1e90d08
 */
#include "ffta.h"

typedef struct TaskParameters080DF75C {
    void *first;
    void *second;
    u16 third;
    u16 fourth;
    u8 fifth;
    u8 unknown_0d[3];
} TaskParameters080DF75C;

typedef struct SchedulerDescriptor080DF75C {
    u16 phase;
    u16 unknown_02;
    TaskParameters080DF75C *parameters;
    u8 unknown_08[12];
    u16 value;
    u8 unknown_16[6];
} SchedulerDescriptor080DF75C;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DE9E0(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DF75C(void *first, void *second, u16 third, u16 fourth,
                    u8 fifth, u16 value, void *parent)
{
    SchedulerDescriptor080DF75C descriptor;
    TaskParameters080DF75C parameters;

    parameters.first = first;
    parameters.second = second;
    parameters.third = third;
    parameters.fourth = fourth;
    parameters.fifth = fifth;
    descriptor.parameters = &parameters;
    descriptor.value = value;
    return func_08005B6C(func_080DE9E0, 0x6C, &descriptor, parent);
}
