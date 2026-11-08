#include "ffta.h"

/* func_0812B7D0 [0x0812B7D0,0x0812B7F0) 32 bytes
 * raw: 00b587b00190684681820448b0216a460023f6f7d3f907b001bc0047f9b51208 */

typedef struct {
    u32 unknown_00;
    void *object;
    u32 unknown_08[3];
    u16 value;
    u16 unknown_16;
    u32 unknown_18;
} TaskDescriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_0812B5F8(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);

void func_0812B7D0(void *object, u16 value)
{
    TaskDescriptor descriptor;

    descriptor.object = object;
    descriptor.value = value;
    func_08121B8C(func_0812B5F8, 0xB0, &descriptor, 0);
}
