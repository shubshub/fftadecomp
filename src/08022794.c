#include "ffta.h"

typedef void (*BufferFiller)(void *destination, u32 value, u8 count);

typedef struct {
    u32 unknown_00;
    u8 *cursor;
    u32 unknown_08;
    u32 size;
} BufferContext;

extern BufferFiller const data_0836D4C0[];

/* 08022794..080227BC: 40 bytes. */
u32 func_08022794(BufferContext *context)
{
    data_0836D4C0[0](context->cursor, 0xFF, context->size);
    context->cursor += context->size;
    return 0;
}
