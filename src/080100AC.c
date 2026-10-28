#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u16 flags;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_0800C64C(void *object);

/* Complete [0x080100AC, 0x080100E0): 52 bytes, 21 instructions. */
void func_080100AC(void *object, u8 enabled)
{
    RenderState *state = func_0800C614(object);

    if (enabled)
        state->flags |= 1;
    else
        state->flags &= 0xFFFE;
    func_0800C64C(object);
}
