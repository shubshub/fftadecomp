#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 type;
} ActionDescriptor;

typedef struct {
    const void *first;
    const void *second;
    u8 unknown_08[0x28];
    const ActionDescriptor *descriptor;
} ActionContext;

extern s32 func_080C7EA4(const void *object, u32 selector);

u32 func_08131484(const ActionContext *context)
{
    u32 result;

    if (context->descriptor->type == 0x5A)
    {
        u32 value = (u32)func_080C7EA4(context->first, 0x26) >> 1;
        if (func_080C7EA4(context->first, 0x26) & 1)
            value++;
        result = value;
    }
    else
    {
        if ((u32)func_080C7EA4(context->second, 0x26) > 1)
            result = 2;
        else
            result = func_080C7EA4(context->second, 0x26);
    }
    return result;
}
