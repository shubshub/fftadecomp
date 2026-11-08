/* 0x080F1184: 36 target bytes, including the callback literal.
 * 00b587b0131c0006000e6a46908201910348342114f7e8fc07b002bc08470000fd0b0f08
 */
#include "ffta.h"

typedef struct SpriteCommand080F1184 {
    u16 phase;
    u16 unknown_02;
    void *owner;
    u8 unknown_08[12];
    u16 index;
    u8 unknown_16[6];
} SpriteCommand080F1184;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080F0BFC(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080F1184(u8 index, void *owner, void *parent)
{
    SpriteCommand080F1184 descriptor;

    descriptor.index = index;
    descriptor.owner = owner;
    return func_08005B6C(func_080F0BFC, 0x34, &descriptor, parent);
}
