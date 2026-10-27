#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u32 unknown_00;
    u8 *cursor;
    u32 unknown_08;
    u32 size;
} BufferContext;

extern BufferInitializer const g_callbacks_0836D4B8[];

/* 08022770..08022794: 36 bytes. */
u32 func_08022770(BufferContext *context)
{
    g_callbacks_0836D4B8[0](context->cursor, context->size);
    context->cursor += context->size;
    return 0;
}
