#include "ffta.h"

/* 0x080DDC18..0x080DDD9E: 390 bytes. */
typedef struct {
    u8 type;
    s8 x;
    s8 y;
    u8 direction;
} EffectSpawnEntry;

typedef struct {
    u32 owner;
    u8 count;
    u8 unknown_05[3];
    u8 *finished;
    const EffectSpawnEntry *entries;
    u16 delay;
    u16 flags;
    s8 special_parameter;
    u8 unknown_15;
    u16 sound;
} EffectSpawnConfig;

typedef struct {
    u16 state;
    u16 unknown_02;
    const EffectSpawnConfig *config;
} EffectSpawnCommand;

typedef struct {
    u32 owner;
    u8 count;
    u8 unknown_05[3];
    u8 *finished;
    const EffectSpawnEntry *entries;
    u16 delay;
    u16 flags;
    u32 handles[4];
    u8 special_finished;
    s8 special_parameter;
    u16 sound;
    u32 special_handle;
} EffectSpawnState;

extern u32 func_080DE4B0(u32 owner, u8 *finished, u8 type, s8 x,
                         s8 y, u8 direction, u32 flags, void *context);
extern u32 func_080DBA5C(u32 handle);
extern void func_080DBA50(u32 handle);
extern void func_08141570(u8 mode, u16 sound);
extern void func_08141520(u16 sound);

static inline void play_completion_sound(u16 sound, u32 flags)
{
    if (flags & 1) {
        u8 mode = 0;

        if (flags & 2)
            mode = 1;
        else if (flags & 4)
            mode = 2;
        if (mode)
            func_08141570(mode, sound);
        else
            func_08141520(sound);
    }
}

u32 func_080DDC18(void *context, EffectSpawnCommand *command,
                  EffectSpawnState *state)
{
    switch (command->state) {
    case 0: {
        const EffectSpawnConfig *config = command->config;

        state->owner = config->owner;
        state->count = config->count;
        state->finished = config->finished;
        state->entries = config->entries;
        state->delay = config->delay + 1;
        state->flags = config->flags;
        if (state->flags & 1) {
            state->sound = config->sound;
            state->special_parameter = config->special_parameter;
            state->special_handle = func_080DE4B0(state->owner,
                &state->special_finished, 0, state->special_parameter,
                0, 0, 0, context);
        }
        break;
    }
    case 1:
        break;
    case 0x100: {
        u8 i;

        state->delay--;
        if (state->delay == 0) {
            for (i = 0; i < state->count; i++) {
                const EffectSpawnEntry *entries = state->entries;
                const EffectSpawnEntry *entry = &entries[i];
                u8 type = entry->type;

                if (type == 2)
                    type = 3;
                state->handles[i] = func_080DE4B0(state->owner,
                    &state->finished[i], type, entry->x, entry->y,
                    entry->direction, 0, context);
            }
            command->state++;
        }
        break;
    }
    case 0x101: {
        u8 i;

        for (i = 0; i < state->count; i++) {
            state->handles[i] = func_080DBA5C(state->handles[i]);
            if (state->handles[i])
                break;
        }
        if (i == state->count && state->special_handle == 0)
            command->state = 2;
        break;
    }
    }
    if (state->special_handle && state->special_finished) {
        play_completion_sound(state->sound, state->flags);
        func_080DBA50(state->special_handle);
        state->special_handle = 0;
    }
    return 0;
}
