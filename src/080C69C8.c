#include "ffta.h"

/* Complete target: [0x080C69C8, 0x080C7078), 1712 bytes, 688 instructions,
   including the 19-entry jump table at 0x080C69E4 and the literal pools.
   Runs the link exchange that func_080C68EC (src/080C68EC.c) sets up: the
   handshakes, the name and record transfers through func_080C5D60's
   command queue, and the arrival of each received unit.  Its only caller
   is func_080C7560 (src/080C7560.c). */

typedef struct {
    void *context;
    u8 unknown_04[4];
    void *buffer;
    u8 unknown_0C[4];
    u16 width;
    u16 mode;
    u8 unknown_14;
    u8 index;
    u8 blocks;
    u8 unknown_17;
    u16 command;
    u16 count;
    u16 commands[34];
} CommandQueue080C5D60;

/* The unit's record, as src/080BAEE8.c declares it: the tile at 0xF6. */
typedef struct {
    u8 unknown_00[0xF6];
    u8 tile_x;
    u8 tile_z;
    s8 direction;
    u8 saved_tile_x;
    u8 saved_tile_z;
} Unit080C69C8;

/* The unit on the map, read at +0, +8, +0xA, +0xC and +0x30 as
 * src/080BAEE8.c's Subject is: y is the height. */
typedef struct {
    Unit080C69C8 *unit;
    u8 unknown_04[4];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x22];
    u32 flags;
} Subject080C69C8;

/* A 0x108-byte slot returned by func_0809A9C0 (src/0809A9C0.c). */
typedef struct {
    u8 *unknown_00;
    u8 unknown_04;
} Record080C69C8;

/* func_080C68EC's InitializerState, with the command queue at +0. */
typedef struct {
    CommandQueue080C5D60 queue;
    void *source;
    void *records[2];
    Subject080C69C8 *object;
    u8 *saved_control;
    void *task;
    u8 index;
    u8 record_count;
    s8 delay;
    u8 unknown_7B;
    u16 current;
    u16 depth;
    u16 history[34];
} State080C69C8;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 current;
    u8 pending;
    u16 x;
    u16 y;
    u8 unknown_08[0x40];
    u16 active;
    u8 unknown_4A[0x46];
} Animation080C69C8;

typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputState;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
    /* Tested as (status & 0xFFFF), as func_08092784 (src/08092784.c) tests
       the same word: 0x080C6B40 loads the 0xFFFF mask (pool word at
       0x080C6B68) before the halfword load at 0x080C6B42, and the pop at
       0x080C6B5E reuses it (`ands r0, r2`). */
    u32 status;
} SystemState;

typedef void (*BufferInitializer080C69C8)(void *destination, u32 bytes);
typedef void (*BufferCopier080C69C8)(void *destination, const void *source,
                                    u32 bytes);

extern BufferInitializer080C69C8 g_callbacks_0836D4B8[];
extern BufferCopier080C69C8 data_0836D4BC[];
extern Animation080C69C8 data_02015744;
extern InputState data_02015738;
extern SystemState data_030028A0;
extern u8 data_02001F1C[];
extern u8 data_02002E78[];
extern u8 g_control_flags_03000940[];
extern const char data_08149A40[];
extern const char data_08149A48[];
extern const char data_08149A50[];
extern const char data_08149A58[];
extern void func_08005028(void);
extern s32 func_08003B1C(const char *first, const char *second);
extern s32 func_08004D68(void);
extern u8 func_080C95A8(u16 index);
extern void func_080C5D60(CommandQueue080C5D60 *queue, void *context,
                         u16 width, u8 mode);
extern u8 func_080C5F94(void *context);
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern u8 *func_0809A9BC(void *context);
extern Record080C69C8 *func_0809A9C0(void *context, s32 index);
extern u8 *func_0809AB0C(void *context);
extern Subject080C69C8 *func_08092440(void *context, Record080C69C8 *record);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void *func_080D3508(u16 id, void *object, u32 arg);
extern void func_080D376C(void);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);
extern u8 func_080D37F8(void);
extern void func_080D3864(void *task);
extern u8 func_080D3878(const void *task);
extern u8 func_080D39B0(void);

/* An inlined copy of func_080C71B4 (src/080C71B4.c). */
static inline void request_animation(u16 request)
{
    u8 value;
    Animation080C69C8 *animation;

    if (!func_080C95A8(13))
        return;
    value = request;
    animation = &data_02015744;
    if (animation->current) {
        if (animation->current == value)
            return;
        animation->flags |= 4;
        animation->pending = value;
    } else {
        g_callbacks_0836D4B8[0](animation, sizeof(*animation));
        animation->current = value;
        animation->x = 216;
        animation->y = 152;
        if (value)
            animation->active = 1;
    }
}

/* The same test as func_080C7560 (src/080C7560.c) and func_080C7078
   (src/080C7078.c). */
static inline u8 input_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }
    if (((data_02015738.flags & 0x20) || data_02015738.count > 13) &&
        (data_030028A0.busy != 0 ||
         (data_030028A0.mode != 3 && data_030028A0.ticks > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

/* As in func_080C7078 (src/080C7078.c). */
static inline u8 queue_update(void *context)
{
    if (input_blocked())
        return 2;
    return func_080C5F94(context);
}

/* Starts a two-way (mode 2) queue transfer of SIZE bytes at DATA.  The
   three uses have two ROM copies (cases 8 and 9 share 0x080C6C62-0x080C6C6C;
   case 5 is 0x080C6D72-0x080C6D7C), and in both the width is set after the
   queue and data registers, as a parameter's value is; a literal width of
   0x140 or 0x108 is set ahead of them. */
static inline void start_transfer(State080C69C8 *state, void *data, u16 size)
{
    func_080C5D60(&state->queue, data, size, 2);
}

/* The state stack's push and pop, as do { } while (0) statement macros (the
   agbcc-era form of src/0804E358.c and src/08010DD0.c).  The ROM has the pop
   eleven times: in cases 4 (0x080C6B54), 5 (0x080C6C8E) and 7 (0x080C6EEC),
   and in the tail at 0x080C7046 that the other eight share.  The macro form
   shows in case 4: the ROM keeps the 0xFFFF mask of the status test in r2,
   where the pop reuses it (`ands r0, r2` at 0x080C6B5E), and the link
   state's base in r3 (0x080C6B38-0x080C6B4C); a plain pop there (an inline
   function, the assignment written out, an expression macro) swaps the two
   registers.  Case 5's pop is written out (see there). */
#define PUSH_STATE(state) \
    do { \
        (state)->history[(state)->depth++] = (state)->current; \
    } while (0)

#define POP_STATE(state) \
    do { \
        (state)->current = (state)->history[--(state)->depth]; \
    } while (0)

u8 func_080C69C8(State080C69C8 *state)
{
    switch (state->current) {
    case 0:
        request_animation(2);
        func_08005028();
        POP_STATE(state);
        break;
    case 1:
        if (func_08003B1C(data_08149A40, data_08149A48)) {
            request_animation(0);
            state->delay = 0;
            state->current = 3;
            PUSH_STATE(state);
            state->current = 4;
        }
        break;
    case 2:
        if (func_08003B1C(data_08149A50, data_08149A58)) {
            request_animation(0);
            state->delay = 0;
            state->current = 3;
            PUSH_STATE(state);
            state->current = 4;
        }
        break;
    case 4:
        if ((data_030028A0.status & 0xFFFF) == 0x101 && data_030028A0.mode == 3)
            POP_STATE(state);
        break;
    case 3:
        if (state->delay <= 7) {
            state->delay++;
            break;
        }
        POP_STATE(state);
        break;
    case 8:
        request_animation(1);
        data_0836D4BC[0](func_0809A9BC(state->source), data_02001F1C, 0x14);
        start_transfer(state, func_0809A9BC(state->source), 0x14);
        state->current = 6;
        break;
    case 9:
        data_0836D4BC[0](func_0809AB0C(state->source), data_02002E78, 0x140);
        request_animation(1);
        start_transfer(state, func_0809AB0C(state->source), 0x140);
        state->current = 6;
        break;
    case 5: {
        Record080C69C8 *record;

        if (state->index + 1 > 2) {
            /* Written out, not POP_STATE: this pop rebuilds the depth
               address from the state register (0x080C6C8E) rather than
               from the index address in r1, and 0x080C6C96 sets r6 = 0
               for the request below between its subtract and its store;
               POP_STATE here compiles to neither. */
            state->current = state->history[--state->depth];
            request_animation(0);
            break;
        }
        request_animation(1);
        record = func_0809A9C0(state->source, state->index);
        if (state->records[state->index] == 0)
            g_callbacks_0836D4B8[0](record, 0x108);
        else
            data_0836D4BC[0](record, state->records[state->index], 0x108);
        start_transfer(state, record, 0x108);
        PUSH_STATE(state);
        state->current = 7;
        PUSH_STATE(state);
        state->current = 6;
        break;
    }
    case 6:
        if (queue_update(&state->queue) == 0) {
            CommandQueue080C5D60 *queue = &state->queue;

            if (queue->buffer) {
                func_08022854(queue->buffer);
                queue->buffer = 0;
            }
            request_animation(0);
            POP_STATE(state);
        }
        break;
    case 7: {
        Record080C69C8 *record = func_0809A9C0(state->source, state->index);
        Subject080C69C8 *object;

        if (record->unknown_04) {
            object = func_08092440(state->source, record);
            object->unit->saved_tile_x = object->unit->tile_x;
            object->unit->saved_tile_z = object->unit->tile_z;
            if (record->unknown_04 == 2)
                record->unknown_00 = func_0809A9BC(state->source);
            object->flags |= 5;
            state->object = object;
            state->index++;
            POP_STATE(state);
            PUSH_STATE(state);
            state->current = 16;
            PUSH_STATE(state);
            state->current = 14;
            PUSH_STATE(state);
            state->current = 12;
            PUSH_STATE(state);
            state->current = 10;
            break;
        }
        state->index++;
        POP_STATE(state);
        break;
    }
    case 10:
        func_08096F3C(state->object->x, state->object->y, state->object->z);
        state->current = 11;
        break;
    case 11:
        if (!func_08096F7C())
            POP_STATE(state);
        break;
    case 12:
        state->saved_control = func_08022840(0x50);
        data_0836D4BC[0](state->saved_control, g_control_flags_03000940, 0x50);
        func_080D376C();
        state->current = 13;
        break;
    case 13:
        if (func_080D37F8() && func_080D39B0())
            POP_STATE(state);
        break;
    case 14:
        state->object->flags &= ~4;
        /* The third argument is the object, already in r2 from
           0x080C6FCA when 0x080C6FDA calls. */
        state->task = func_080D3508(0x165, 0, (u32)state->object);
        state->current = 15;
        break;
    case 15:
        if (func_080D3878(state->task)) {
            func_080D3864(state->task);
            state->task = 0;
            func_0809836C(state->object, 10, state->object->unit->direction, 0);
            POP_STATE(state);
        }
        break;
    case 16:
        func_080D37AC();
        state->current = 17;
        break;
    case 17:
        if (func_080D37C4()) {
            data_0836D4BC[0](g_control_flags_03000940, state->saved_control, 0x50);
            func_08022854(state->saved_control);
            POP_STATE(state);
        }
        break;
    case 18:
        return 0;
    }
    return 1;
}
