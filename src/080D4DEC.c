#include "ffta.h"

/* Complete [0x080D4DEC, 0x080D5128): 828 bytes, 404 instructions, no literal pool.
 * The timed-effect task created by func_080D6098: phase 0x100 spawns every
 * entry that starts at frame 0, phase 0x101 advances the clock, spawns the
 * entries that start on this frame and counts the finished ones.
 */

typedef struct EffectObject EffectObject;

struct Resource {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

/* One 24-byte row of the table passed to func_080D6098.  Across the 536 rows
 * of the 224 tables its callers pass, x and y are often negative (36 and 159
 * rows), depth is always 0 and tile is 576-1021 (an OBJ tile number, the value
 * src/080D5FD8.c computes as (tiles - 0x06010000) >> 5). */
typedef struct {
    const struct Resource *resource;
    u16 index;
    u16 unknown_06;
    s16 x;
    s16 y;
    u16 depth;
    u16 tile;
    u8 priority;
    u8 unknown_11;
    u16 flags;
    u8 palette;
    u8 unknown_15;
    u16 start;
} EffectEntry;

typedef struct TaskParameters {
    u16 x;
    u16 y;
    u16 depth;
    u16 count;
    u8 mode;
    void **outputs;
    const void *entries;
} TaskParameters;

typedef struct TaskRequest {
    u16 state;
    u16 unknown_02;
    TaskParameters *parameters;
    u32 unknown_08[5];
} TaskRequest;

typedef struct {
    s16 x;
    s16 y;
    s16 depth;
    u16 count;
    u16 time;
    u8 mode;
    u8 unknown_0B;
    s16 order;
    u8 flags;
    u8 unknown_0F;
    s16 tile_offset;
    u16 unknown_12;
    void **outputs;
    const EffectEntry *entries;
} EffectState;

extern u32 func_08011348(const void *entries, const void *data, u16 index,
                         u8 layer, s16 x, s16 y, s16 width, s16 height,
                         u8 mode, u16 attributes);
extern void func_08011138(EffectObject *object, u8 palette);
extern void func_08011058(EffectObject *object, s16 order);
extern void func_0801121C(EffectObject *object, s16 value);
extern u8 func_08010FF0(EffectObject *object);
extern void func_08011428(EffectObject *object);
extern void func_080D5F74(void **objects, u16 count);

/* Creates the effect object for one entry, offset by the task's position.
 * Both spawn sites inline it: 0x080D4E96..0x080D4F58 and 0x080D502E..
 * 0x080D50F0 are the same code, and each loads the six task fields in this
 * parameter order (ldrsh +0, +2, +4, ldrb +0xA, ldrsh +0xC, +0x10) before
 * entry->resource.  Neither direct code (774 bytes) nor s16 or s32 copies
 * at the top of each block (840 / 838 bytes) loads them that way. */
static inline EffectObject *spawn_entry(const EffectEntry *entry, s16 x, s16 y,
                                        s16 depth, u8 mode, s16 order,
                                        s16 tile_offset, u16 flags)
{
    const struct Resource *resource = entry->resource;
    const void *frames = resource->data;
    const void *data = (const u8 *)resource + resource->offset;
    u16 attributes = flags | entry->flags;
    EffectObject *object;

    if (resource->flags & 4)
        attributes |= 0x2000;
    if (resource->flags & 8)
        attributes |= 0x4000;
    object = (EffectObject *)func_08011348(frames, data, entry->index, mode,
                                           entry->x + x, entry->y + y,
                                           entry->depth + depth,
                                           entry->tile + tile_offset,
                                           entry->priority, attributes);
    if (mode != 2)
        func_08011138(object, entry->palette);
    if (order != 0)
        func_08011058(object, order);
    return object;
}

u32 func_080D4DEC(void *task, TaskRequest *request, EffectState *state)
{
    switch (request->state) {
    case 0: {
        const TaskParameters *parameters = request->parameters;

        state->x = parameters->x;
        state->y = parameters->y;
        state->depth = parameters->depth;
        state->count = parameters->count;
        state->mode = parameters->mode;
        state->outputs = parameters->outputs;
        state->entries = parameters->entries;
        break;
    }
    case 1:
        func_080D5F74(state->outputs, state->count);
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
                state->outputs[i] = spawn_entry(entry, state->x, state->y,
                                                state->depth, state->mode,
                                                state->order,
                                                state->tile_offset, flags);
                if (state->flags & 8)
                    func_0801121C(state->outputs[i], -1);
            }
        }
        request->state++;
        break;
    }
    case 0x101: {
        u16 i;
        u16 finished;
        u16 flags = 0;

        state->time++;
        for (i = 0, finished = 0; i < state->count; i++) {
            if (state->outputs[i] != 0) {
                if (func_08010FF0(state->outputs[i])) {
                    if (!(state->flags & 1)) {
                        func_08011428(state->outputs[i]);
                        state->outputs[i] = 0;
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
                    state->outputs[i] = spawn_entry(entry, state->x,
                                                    state->y, state->depth,
                                                    state->mode,
                                                    state->order,
                                                    state->tile_offset, flags);
                }
            }
        }
        if (finished == state->count)
            request->state = 2;
        break;
    }
    }
    return 0;
}
