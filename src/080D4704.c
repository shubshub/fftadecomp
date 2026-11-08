#include "ffta.h"

/* 0x080D4704: 32 target bytes, including the callback literal.
 * 00b587b00b1c6a460021918201900348182131f729fa07b002bc08479d440d08
 */
typedef struct SchedulerDescriptor080D4704 {
    u16 state;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[0x0c];
    u16 first;
    u16 unknown_16;
    u8 unknown_18[4];
} SchedulerDescriptor080D4704;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D449C(void *task, SchedulerDescriptor080D4704 *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D4704(void *value, void *parent)
{
    SchedulerDescriptor080D4704 descriptor;

    descriptor.first = 0;
    descriptor.value = value;
    return func_08005B6C((TaskCallback)func_080D449C, 0x18, &descriptor, parent);
}
