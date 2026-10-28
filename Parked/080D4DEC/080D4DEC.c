#include "ffta.h"

/* 0x080D4DEC..0x080D5128: 828 bytes. */
typedef struct EffectObject EffectObject;

typedef struct {
    const u8 *data;
    u16 tile;
    u16 unknown_06;
    u16 x;
    u16 y;
    u16 z;
    u16 depth;
    u8 priority;
    u8 unknown_11;
    u16 flags;
    u8 palette;
    u8 unknown_15;
    u16 start;
} EffectEntry;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 count;
    u8 mode;
    u8 unknown_09[3];
    EffectObject **objects;
    const EffectEntry *entries;
} EffectConfig;

typedef struct {
    u16 state;
    u16 unknown_02;
    const EffectConfig *config;
} EffectCommand;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u16 count;
    u16 time;
    u8 mode;
    u8 unknown_0B;
    s16 transform;
    u8 flags;
    u8 unknown_0F;
    s16 depth;
    u16 unknown_12;
    EffectObject **objects;
    const EffectEntry *entries;
} EffectState;

extern EffectObject *func_08011348(const u8 *, const u8 *, u16, u8,
                                  s16, s16, s16, s16, u8, u16);
extern void func_08011138(EffectObject *, u8);
extern void func_08011058(EffectObject *, s16);
extern void func_0801121C(EffectObject *, s32);
extern u8 func_08010FF0(EffectObject *);
extern void func_08011428(EffectObject *);
extern void func_080D5F74(EffectObject **, u16);

u32 func_080D4DEC(void *unused, EffectCommand *command, EffectState *state)
{
    switch (command->state) {
    case 0: {
        const EffectConfig *config = command->config;

        state->x = config->x;
        state->y = config->y;
        state->z = config->z;
        state->count = config->count;
        state->mode = config->mode;
        state->objects = config->objects;
        state->entries = config->entries;
        break;
    }
    case 1:
        func_080D5F74(state->objects, state->count);
        break;
    case 0x100: {
        u16 flags = 0;
        u16 i;

        for (i = 0; i < state->count; i++) {
            const EffectEntry *entry = &state->entries[i];

            if (entry->start == 0) {
                if (state->flags & 2)
                    flags |= 0x20;
                if (state->flags & 4)
                    flags |= 0x1000;
                {
                    s32 x = state->x;
                    s32 y = state->y;
                    s32 z = state->z;
                    u8 mode = state->mode;
                    s32 transform = state->transform;
                    s32 depth = state->depth;
                    const u8 *data = entry->data;
                    const u8 *graphics = data + 4;
                    u8 offset_low = data[2];
                    u8 offset_high = data[3];
                    const u8 *animation = data + ((offset_high << 8) | offset_low);
                    u16 render_flags = flags | entry->flags;
                    u8 flags_low = data[0];
                    u8 flags_high = data[1];
                    u32 data_flags = (flags_high << 8) | flags_low;
                    EffectObject *object;

                    if (data_flags & 4)
                        render_flags |= 0x2000;
                    if (data_flags & 8)
                        render_flags |= 0x4000;
                    object = func_08011348(graphics, animation, entry->tile, mode,
                                          (s16)(entry->x + x), (s16)(entry->y + y),
                                          (s16)(entry->z + z), (s16)(entry->depth + depth),
                                          entry->priority, render_flags);
                    if (mode != 2)
                        func_08011138(object, entry->palette);
                    if (transform != 0)
                        func_08011058(object, transform);
                    state->objects[i] = object;
                    if (state->flags & 8)
                        func_0801121C(object, -1);
                }
            }
        }
        command->state++;
        break;
    }
    case 0x101: {
        u16 flags = 0;
        u16 i;
        u16 finished;

        state->time++;
        i = 0;
        finished = 0;
        for (; i < state->count; i++) {
            if (state->objects[i] != 0) {
                if (func_08010FF0(state->objects[i])) {
                    if (!(state->flags & 1)) {
                        func_08011428(state->objects[i]);
                        state->objects[i] = 0;
                    }
                    finished++;
                }
            } else {
                const EffectEntry *entry = &state->entries[i];

                if (entry->start < state->time) {
                    finished++;
                } else if (entry->start == state->time) {
                    if (state->flags & 2)
                        flags |= 0x20;
                    if (state->flags & 4)
                        flags |= 0x1000;
                    {
                    s32 x = state->x;
                    s32 y = state->y;
                    s32 z = state->z;
                    u8 mode = state->mode;
                    s32 transform = state->transform;
                    s32 depth = state->depth;
                    const u8 *data = entry->data;
                    const u8 *graphics = data + 4;
                    u8 offset_low = data[2];
                    u8 offset_high = data[3];
                    const u8 *animation = data + ((offset_high << 8) | offset_low);
                    u16 render_flags = flags | entry->flags;
                    u8 flags_low = data[0];
                    u8 flags_high = data[1];
                    u32 data_flags = (flags_high << 8) | flags_low;
                    EffectObject *object;

                    if (data_flags & 4)
                        render_flags |= 0x2000;
                    if (data_flags & 8)
                        render_flags |= 0x4000;
                    object = func_08011348(graphics, animation, entry->tile, mode,
                                          (s16)(entry->x + x), (s16)(entry->y + y),
                                          (s16)(entry->z + z), (s16)(entry->depth + depth),
                                          entry->priority, render_flags);
                    if (mode != 2)
                        func_08011138(object, entry->palette);
                    if (transform != 0)
                        func_08011058(object, transform);
                    state->objects[i] = object;
                    }
                }
            }
        }
        if (finished == state->count)
            command->state = 2;
        break;
    }
    }
    return 0;
}
