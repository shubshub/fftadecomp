#include "ffta.h"

// Complete target: [0x080C7078, 0x080C71B2), 314 bytes, including the
// jump table and literal pools.

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

typedef struct {
    void *context;
    CommandQueue080C5D60 queue;
    u16 phase;
} State080C7078;

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
} SystemState;

extern InputState data_02015738;
extern SystemState data_030028A0;
extern const char data_08149A70[];
extern const char data_08149A7C[];
extern void func_08005028(void);
extern s32 func_08003B1C(const char *first, const char *second);
extern s32 func_08004D68(void);
extern void func_080C5D60(CommandQueue080C5D60 *queue, void *context,
                         u16 width, u8 mode);
extern u8 func_080C5F94(void *context);
extern void func_08022854(void *allocation);

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

static inline u8 queue_update(void *context)
{
    if (input_blocked())
        return 2;
    return func_080C5F94(context);
}

u8 func_080C7078(State080C7078 *state, u8 mode)
{
    CommandQueue080C5D60 *queue;

    switch (state->phase) {
    case 0:
        func_08005028();
        state->phase = 1;
        break;
    case 1:
        if (func_08003B1C(data_08149A70, data_08149A7C))
            state->phase = 2;
        break;
    case 2:
        if (mode)
            func_080C5D60(&state->queue, state->context, 0x18, 0);
        else
            func_080C5D60(&state->queue, state->context, 0x18, 1);
        state->phase = 3;
        break;
    case 3:
        if (queue_update(&state->queue) == 0) {
            queue = &state->queue;
            if (queue->buffer) {
                func_08022854(queue->buffer);
                queue->buffer = 0;
            }
            state->phase = 4;
        }
        break;
    case 4:
        return 0;
    }
    return 1;
}
