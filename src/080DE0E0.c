/* 0x080DE0E0: complete 44-byte caller, including the callback literal.
 * 10b587b0099c1206120e0190029168468282c38204480c216a46231c27f736fd07b010bc02bc0847add90d08
 */
#include "ffta.h"

typedef struct SchedulerDescriptor080DE0E0 {
    u8 unknown_00[4];
    void *first_value;
    void *second_value;
    u8 unknown_0C[8];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} SchedulerDescriptor080DE0E0;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DD9AC(void *task, SchedulerDescriptor080DE0E0 *descriptor,
                  void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080DE0E0(void *first_value, void *second_value, u8 first,
                    u16 second, void *parent)
{
    SchedulerDescriptor080DE0E0 descriptor;

    descriptor.first_value = first_value;
    descriptor.second_value = second_value;
    descriptor.first = first;
    descriptor.second = second;
    return func_08005B6C((TaskCallback)func_080DD9AC, 0xC, &descriptor, parent);
}
