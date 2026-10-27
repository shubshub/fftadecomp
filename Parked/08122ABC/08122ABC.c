#include "ffta.h"

typedef struct CommandState CommandState;
typedef u32 (*CommandHandler)(CommandState *state, const u8 *command);

typedef struct {
    u16 length;
    CommandHandler handler;
} __attribute__((packed)) CommandEntry;

struct CommandState {
    s16 position;
    u8 unknown_02[0xA];
    const u8 *commands;
};

extern const CommandEntry data_083A7EE4[];

/* 08122ABC..08122B14: 88 bytes. */
u32 func_08122ABC(CommandState *state)
{
    const CommandEntry *table = data_083A7EE4;
    u32 result;

    do {
        const u8 *command = state->commands + state->position;
        const CommandEntry *entry = &table[*command];

        result = entry->handler(state, command);
        state->position += entry->length;
    } while (result == 0x110);

    return result;
}
