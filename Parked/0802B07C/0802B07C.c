#include "ffta.h"

/* 0x0802B07C..0x0802B108: 140 bytes. */
typedef struct {
    u8 unknown_00[0xC];
    u16 *buffer;
    u8 unknown_10[5];
    u8 width;
    u8 height;
    u8 unknown_17[3];
    u16 position;
} ScrollContext;

extern u16 data_02003CB0[];
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0802B07C(ScrollContext *context, u16 direction)
{
    u16 *temporary = data_02003CB0;
    u16 total = context->width * (u16)(context->height * 2);
    u16 stride = context->width * 2;

    if (direction == 0x80) {
        func_0814186C(context->buffer + stride, temporary, (total - stride) & 0x1FFFFF);
        func_0814186C(temporary, context->buffer, (total - stride) & 0x1FFFFF);
        context->position++;
    } else if (direction == 0x40) {
        func_0814186C(context->buffer, temporary, (total - stride) & 0x1FFFFF);
        func_0814186C(temporary, context->buffer + stride, (total - stride) & 0x1FFFFF);
        context->position--;
    }
}
