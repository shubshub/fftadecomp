#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    const u8 *source;
    u8 *destination;
    u32 unknown_08;
    u32 size;
} CopyContext;

extern BufferCopier const data_0836D4BC[];

/* 080227BC..080227E8: 44 bytes. */
u32 func_080227BC(CopyContext *context)
{
    data_0836D4BC[0](context->destination, context->source, context->size);
    context->destination += context->size;
    context->source += context->size;
    return 0;
}
