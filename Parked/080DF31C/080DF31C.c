#include "ffta.h"
#include "control_flags.h"

// 0x080DF31C .. 0x080DF640: 804 bytes.

typedef struct {
    u8 layer;
    u8 palette;
    u8 priority;
    u8 unknown_03;
    u16 width;
    u16 height;
    void *source;
    void *destination;
} DF31CSource;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    const DF31CSource *source;
    u8 unknown_0C[8];
    u16 delay;
    u16 flags;
} DF31CDescriptor;

typedef struct {
    u8 unknown_00[14];
    u16 size;
    u8 priority;
    u8 unknown_11[7];
} DF31CEntry;

typedef struct {
    u16 delay;
    s16 x;
    s16 y;
    u16 flags;
    void *object;
    void *outputs[2];
    void *coordinate_task;
    void *script;
    void *object_task;
    void *effect;
    u8 layer;
    u8 palette;
    u8 priority;
    u16 width;
    u16 height;
    void *source;
    void *destination;
    DF31CEntry entries[2];
} DF31CState;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier const data_0836D4BC[];
extern const DF31CEntry data_0839562C[2];
extern const u8 data_0839565C[];
extern const u8 data_08395668[];
extern const u16 data_08149B80[4];
extern u16 data_03003860[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080DC1E8(void *object, u8 first, u8 second, u8 mode,
                           void *source, void *destination, void *parent);
extern void *func_080DBA5C(void *task);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080DC224(void *object, s16 x, s16 y, s16 *out_x, s16 *out_y);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_081482D4(const u16 *source, u16 *destination, u16 count,
                          u8 amount);
extern void *func_080D3E9C(const void *data, void *parent);
extern u16 func_080035A8(u8 layer);
extern void *func_080D3F08(void *script);
extern void func_080DBEB4(void *object, u8 value);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode, u16 count,
                           void **outputs, const void *entries, void *parent);
extern u16 func_080035D0(u8 layer);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags, u16 delay,
                           void *parent);
extern void *func_080D6134(void *task);

u32 func_080DF31C(void *task, DF31CDescriptor *descriptor, DF31CState *state)
{
    if (state->flags & 0x8000)
        return 0;

    switch (descriptor->state) {
    case 0: {
        const DF31CSource *source;

        state->object = descriptor->object;
        source = descriptor->source;
        state->layer = source->layer;
        state->palette = source->palette;
        state->priority = source->priority;
        state->width = source->width;
        state->height = source->height;
        state->source = source->source;
        state->destination = source->destination;
        data_0836D4BC[0](state->entries, data_0839562C, sizeof(state->entries));
        state->entries[0].size = state->width;
        state->entries[0].priority = state->priority;
        state->entries[1].size = state->height;
        state->entries[1].priority = state->priority;
        state->object_task = func_080DC1E8(state->object, 0, 0, state->palette,
                                           state->source, state->destination,
                                           task);
        state->delay = descriptor->delay + 1;
        state->flags = descriptor->flags;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (state->delay != 0) {
            state->delay--;
            if (state->delay != 0)
                break;
        }
        state->object_task = func_080DBA5C(state->object_task);
        if (state->object_task)
            break;
        descriptor->state++;
        break;
    case 0x101: {
        u16 controls[4];
        s16 offset_x;
        s16 offset_y;
        u16 control;

        func_081443FC(controls, data_08149B80, sizeof(controls));
        if (state->delay != 0) {
            state->delay--;
            if (state->delay != 0)
                break;
        }
        {
            u16 mirrored = state->flags & 8;
            u32 index = mirrored != 0;

            u32 attributes = func_08003A74((u32)state->destination);

            attributes |= func_08003A80(0x06008000);
            control = attributes | controls[index];
        }
        func_080034B8(control, state->layer);
        func_080DBDC8(state->object, &state->x, &state->y);
        func_080DC224(state->object, state->x, state->y, &offset_x, &offset_y);
        func_08003508(offset_x, state->layer);
        func_08003558(offset_y, state->layer);
        if (!(state->flags & 4)) {
            func_081482D4(&data_03003860[state->palette * 16],
                          &data_03003860[state->palette * 16], 16, 8);
            state->script = func_080D3E9C(data_0839565C, task);
        }
        g_control_flags_03000940.display |= func_080035A8(state->layer);
        descriptor->state++;
        break;
    }
    case 0x102:
        state->script = func_080D3F08(state->script);
        if (state->script)
            break;
        if (state->flags & 2)
            state->flags |= 0x8000;
        descriptor->state++;
        break;
    case 0x103: {
        s16 offset;

        if (!(state->flags & 1))
            func_080DBEB4(state->object, 0);
        offset = 0;
        if (state->flags & 0x20)
            offset = -20;
        state->coordinate_task = func_080D6098(state->x, offset + state->y, 0,
                                               1, 2, state->outputs,
                                               state->entries, task);
        g_control_flags_03000940.winout_hi =
            0x3F & ~func_080035D0(state->layer);
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.display |= 0x8000;
        if (!(state->flags & 0x40))
            state->effect = func_080DFD8C(data_08395668, 1, 4, 0, task);
        state->delay = 0x46;
        descriptor->state++;
        break;
    }
    case 0x104:
        if (state->delay != 0) {
            state->delay--;
            if (state->delay == 0) {
                g_control_flags_03000940.display &=
                    ~func_080035A8(state->layer);
                g_control_flags_03000940.display &= ~0x8000;
            }
        }
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task == 0)
            descriptor->state = 2;
        break;
    }
    return 0;
}
