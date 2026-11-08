/* 0x080EDB98: 36 target bytes, including the callback literal.
 * 00b587b0131c0906090e6a46918201900348342117f7deff07b002bc0847000001da0e08
 */
#include "ffta.h"

typedef struct Descriptor080EDB98 {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0xC];
    u16 variant;
    u8 unknown_16[6];
} Descriptor080EDB98;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080EDA00(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080EDB98(void *actor, u8 variant, void *parent)
{
    Descriptor080EDB98 descriptor;

    descriptor.variant = variant;
    descriptor.actor = actor;
    return func_08005B6C(func_080EDA00, 0x34, &descriptor, parent);
}
