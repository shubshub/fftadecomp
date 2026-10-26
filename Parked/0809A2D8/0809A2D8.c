#include "ffta.h"

void func_080975DC(void *context, u16 index, s8 value, s32 enabled);
void func_08097704(void *context, u16 index, s8 value);

void func_0809A2D8(void *context, u32 requested_index, s32 requested_value)
{
    u16 index = requested_index;
    s8 value = requested_value;

    func_080975DC(context, index, value, 1);
    func_08097704(context, index, value);
}
