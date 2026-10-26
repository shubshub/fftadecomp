#include "ffta.h"

typedef struct {
    u8 unknown_00[0x4c];
    u8 first[0x14];
    u8 second[0x14];
} Object0808537C;

extern void func_080812E8(void *context, void *entry, s32 enabled);

/* 0x0808537C..0x080853A0: 36 bytes, 16 instructions. */
void func_0808537C(void *context, Object0808537C *object, s32 enabled)
{
    func_080812E8(context, object->first, enabled);
    if (enabled)
        func_080812E8(context, object->second, enabled);
}
