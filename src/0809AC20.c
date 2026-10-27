#include "ffta.h"

typedef struct {
    u32 count;
    void **cursor;
} OutputContext;

/* 0809AC20..0809AC30: 16 bytes. */
u32 func_0809AC20(void *value, OutputContext *context)
{
    void **cursor = context->cursor;

    *cursor++ = value;
    context->count++;
    context->cursor = cursor;
    return 1;
}
