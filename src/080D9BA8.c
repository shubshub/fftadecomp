#include "ffta.h"

/* 0x080D9BA8..0x080D9BC0: 24 bytes. */
typedef struct {
    u32 unknown_00;
    u32 handle;
} NestedHandleState;

extern NestedHandleState *func_08005BFC(u32 handle);
extern void func_0800C628(u32 handle, u8 value);

void func_080D9BA8(u32 handle, u8 value)
{
    NestedHandleState *state = func_08005BFC(handle);

    func_0800C628(state->handle, value);
}
