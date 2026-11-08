#include "ffta.h"

/* 0x080E5694: 28 target bytes, including the callback literal.
 * 00b587b0031c04482c216a4620f764fa07b002bc0847000011530e08
 */
typedef struct SchedulerDescriptor080E5694 {
    u16 unknown_00;
    u8 unknown_02[2];
    void *unknown_04;
    u8 unknown_08[0x0c];
    u16 unknown_14;
    u16 unknown_16;
    u8 unknown_18[4];
} SchedulerDescriptor080E5694;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080E5310(void *task, SchedulerDescriptor080E5694 *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080E5694(void *parent)
{
    /* The original passes this descriptor without initialising any field. */
    SchedulerDescriptor080E5694 descriptor;

    return func_08005B6C((TaskCallback)func_080E5310, 0x2C, &descriptor, parent);
}
