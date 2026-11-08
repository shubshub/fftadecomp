/* 0x080F11A8: 36 target bytes, including the callback literal.
 * 00b587b0131c0006000e6a469082019103481c2114f7d6fc07b002bc08470000590d0f08
 */
#include "ffta.h"

typedef struct SpriteCommand080F11A8 {
    u16 phase;
    u16 unknown_02;
    void *owner;
    u8 unknown_08[12];
    u16 index;
    u8 unknown_16[6];
} SpriteCommand080F11A8;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080F0D58(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080F11A8(u8 index, void *owner, void *parent)
{
    SpriteCommand080F11A8 descriptor;

    descriptor.index = index;
    descriptor.owner = owner;
    return func_08005B6C(func_080F0D58, 0x1C, &descriptor, parent);
}
