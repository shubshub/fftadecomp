#include "ffta.h"

typedef struct {
    u8 unknown_00[0x40];
    const u8 *cursor;
} CommandContext;

typedef void (*CommandHandler)(void *owner, CommandContext *context);

extern CommandHandler const data_0836D340[];

/* 081464C4..081464E4: 32 bytes. */
void func_081464C4(void *owner, CommandContext *context)
{
    u8 command = *context->cursor++;

    data_0836D340[command](owner, context);
}
