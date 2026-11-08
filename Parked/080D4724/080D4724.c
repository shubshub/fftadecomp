#include "ffta.h"

typedef struct SchedulerDescriptor080D4724 {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[12];
    u16 flag;
    u8 unknown_16[6];
} SchedulerDescriptor080D4724;

typedef u32 (*SchedulerCallback080D4724)(void *task, void *descriptor,
                                       void *payload);

u32 func_080D449C(void *task, SchedulerDescriptor080D4724 *descriptor,
                  void *payload);
u32 func_08005B6C(SchedulerCallback080D4724 callback, u16 payload_size,
                  void *descriptor, void *parent);
void func_080D4820(u32 handle, u16 value);

/* 0x080D4724..0x080D4754: 48 target bytes, including the callback literal.
 * 30b587b00b1c15042d0c6a460021918201900648182131f717fa041c291c00f06df8
 * 201c07b030bc02bc08479d440d08
 */
u32 func_080D4724(void *value, void *parent, u16 param)
{
    SchedulerDescriptor080D4724 descriptor;
    u32 handle;

    descriptor.flag = 0;
    descriptor.value = value;
    handle = func_08005B6C((SchedulerCallback080D4724)func_080D449C, 0x18,
                           &descriptor, parent);
    func_080D4820(handle, param);
    return handle;
}
