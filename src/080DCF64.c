/* 0x080DCF64: complete 128-byte caller, including the callback literal.
 * f0b58ab08c460f99109c119d129e1b0409040f0c2404240c2d042d0c3604360c00906846
 * 0271062242716946042088716846c2711a0c1b14012149428b4200d04271380400148842
 * 01d06846877120040014884201d06846c4716046029003aa9582d6826846049004483821
 * 139b28f7cbfd0ab0f0bc02bc084700005dc50d08
 */
#include "ffta.h"

typedef struct Parameters080DCF64 {
    void *first_value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    void *second_value;
} Parameters080DCF64;

typedef struct SchedulerDescriptor080DCF64 {
    u16 state;
    u8 unknown_02[2];
    const Parameters080DCF64 *parameters;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} SchedulerDescriptor080DCF64;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DC55C(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

static inline void *start_task(const Parameters080DCF64 *parameters,
                               u16 first, u16 second, void *parent)
{
    SchedulerDescriptor080DCF64 descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.parameters = parameters;
    return func_08005B6C(func_080DC55C, 0x38, &descriptor, parent);
}

void *func_080DCF64(void *first_value, void *second_value, u8 kind,
                    u16 override_05, u16 override_06, u16 override_07, u16 first,
                    u16 second, void *parent)
{
    Parameters080DCF64 parameters;

    parameters.first_value = first_value;
    parameters.kind = kind;
    parameters.unknown_05 = 6;
    parameters.unknown_06 = 4;
    parameters.unknown_07 = 6;
    if ((s16)override_05 != -1)
        parameters.unknown_05 = override_05;
    if ((s16)override_06 != -1)
        parameters.unknown_06 = override_06;
    if ((s16)override_07 != -1)
        parameters.unknown_07 = override_07;
    parameters.second_value = second_value;
    return start_task(&parameters, first, second, parent);
}
