/* 0x080DD8C4: complete 60-byte caller, including the callback literal.
 * 70b58ab00e9d0f9e009068460271062444716a46042090716846c471029103aa9382d582
 * 049004483821331c28f73cf90ab070bc02bc08475dc50d08
 */
#include "ffta.h"

typedef struct Parameters080DD8C4 {
    void *first_value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    void *second_value;
} Parameters080DD8C4;

typedef struct SchedulerDescriptor080DD8C4 {
    u16 state;
    u8 unknown_02[2];
    const Parameters080DD8C4 *parameters;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} SchedulerDescriptor080DD8C4;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DC55C(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

static inline void *start_task(const Parameters080DD8C4 *parameters,
                               u16 first, u16 second, void *parent)
{
    SchedulerDescriptor080DD8C4 descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.parameters = parameters;
    return func_08005B6C(func_080DC55C, 0x38, &descriptor, parent);
}

void *func_080DD8C4(void *first_value, void *second_value, u8 kind,
                    u16 first, u16 second, void *parent)
{
    Parameters080DD8C4 parameters;

    parameters.first_value = first_value;
    parameters.kind = kind;
    parameters.unknown_05 = 6;
    parameters.unknown_06 = 4;
    parameters.unknown_07 = 6;
    parameters.second_value = second_value;
    return start_task(&parameters, first, second, parent);
}
