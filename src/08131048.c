#include "ffta.h"

typedef struct {
    void *first;
    void *second;
    u8 unknown_08[0x28];
    const u8 *command;
} CommandContext;

typedef u8 (*CommandHandler)(CommandContext *context);

extern CommandHandler const data_083A8604[];

/* 08131048..0813107C: 52 bytes. */
u8 func_08131048(CommandContext *context)
{
    if (context->first == 0 || context->second == 0)
        return 0;

    return data_083A8604[*context->command](context);
}
