#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *context;
    u8 unknown_08[0x0C];
    u16 flags;
} PanelRequest;

typedef struct {
    u16 next_phase;
    u16 unknown_02;
    s16 x;
    s16 y;
    s16 overlay_x;
    s16 overlay_y;
    void *context;
    u16 flags;
    u8 status;
    u8 width;
    u8 selection;
    u8 unknown_15[3];
    u8 transfer_count;
    u8 transferred;
    u16 transfer_size;
    const u8 *source;
    u8 *destination;
    void *resource;
} PanelState;

typedef struct {
    u32 unknown_00;
    u16 *scroll;
} Background;

typedef struct {
    u8 unknown_00[8];
    void *field_08;
    u8 unknown_0C[0x1F90];
    u8 copy_data[0x60];
} DisplayState;

typedef void (*CopyFunction)(void *destination, const void *source, u32 size);

extern DisplayState *data_0200F440;
extern Background data_030008B0;
extern Background data_03000990;
extern u16 g_control_flags_03000940;
extern u8 data_06008000[];
extern u8 data_0600E000[];
extern u8 data_06005000[];
extern u8 data_03003B20[];
extern CopyFunction data_0836D4BC[];

extern void func_0801E458(u32 layer, u32 enabled, u32 priority, u32 first,
                         u32 second, void *tiles, void *map);
extern void func_0802CABC(PanelState *state, u8 selection);
extern void func_0802CBD4(PanelState *state, u8 selection);
extern void func_0802D05C(PanelState *state);
extern void func_0802D014(PanelState *state);
extern void func_0802CEAC(PanelState *state);
extern void func_0802CFB0(PanelState *state);
extern void *func_0802BA08(void);
extern void func_08000ADC(void *request, const void *source,
                         void *destination, u32 words);

/* Complete target [0x0802D0B0, 0x0802D520): 1136 bytes, 461 instructions. */
u32 func_0802D0B0(void *unused, PanelRequest *request, PanelState *state)
{
    u16 hidden;

    switch (request->phase)
    {
    case 1:
        if (data_0200F440 != 0)
            data_0200F440->field_08 = 0;
        break;

    case 0:
        func_0801E458(2, 1, 0, 0, 0, data_06008000, data_0600E000);
        func_0801E458(3, 1, 1, 0, 0, data_06008000, data_06005000);
        g_control_flags_03000940 |= 0xC00;
        state->status = 1;
        state->context = request->context;
        state->flags = request->flags;
        state->x = -136;
        state->y = 13;
        state->overlay_x = -136;
        state->overlay_y = 152;
        *data_030008B0.scroll = 0x200 - state->x;
        *data_03000990.scroll = 0x200 - state->x;
        break;

    case 0x105:
        if (state->status & 0x10)
            func_0802D05C(state);
        break;

    case 0x10D:
        request->phase = 0x100;
        break;

    case 0x100:
        state->selection = 7;
        func_0802CABC(state, 7);
        state->next_phase = 0x101;
        request->phase = 0x10B;
        *data_030008B0.scroll = 0x200 - state->x;
        *data_03000990.scroll = 0x200 - state->x;
        break;

    case 0x10A:
        state->context = request->context;
        state->flags = request->flags;
        state->selection = (state->flags >> 4) & 1;
        func_0802CABC(state, state->selection);
        hidden = state->flags & 0x10;
        state->next_phase = hidden ? 0x10C : 0x102;
        if (hidden)
            state->overlay_x = -136;
        request->phase = 0x10B;
        break;

    case 0x10B:
        func_0802CBD4(state, state->selection);
        func_0802D05C(state);
        request->phase = state->next_phase;
        break;

    case 0x101:
        state->x += 18;
        if (state->transferred < state->transfer_count)
        {
            func_08000ADC(func_0802BA08(), state->source, state->destination,
                          state->transfer_size >> 2);
            state->destination += state->transfer_size;
            state->source += state->transfer_size;
            if (++state->transferred == state->transfer_count)
                data_0836D4BC[0](data_03003B20, data_0200F440->copy_data, 0x60);
        }
        if (state->x >= 0 && state->transferred == state->transfer_count)
        {
            state->x = 0;
            state->status = 2;
            request->phase = 0x102;
        }
        state->overlay_x = state->x;
        func_0802D05C(state);
        *data_030008B0.scroll = 0x200 - state->x;
        *data_03000990.scroll = 0x200 - state->x;
        break;

    case 0x10C:
        state->overlay_x += 18;
        if (state->transferred < state->transfer_count)
        {
            func_08000ADC(func_0802BA08(), state->source, state->destination,
                          state->transfer_size >> 2);
            state->destination += state->transfer_size;
            state->source += state->transfer_size;
            if (++state->transferred == state->transfer_count)
                data_0836D4BC[0](data_03003B20, data_0200F440->copy_data, 0x60);
        }
        if (state->overlay_x >= 0 && state->transferred == state->transfer_count)
        {
            state->overlay_x = state->x;
            state->status = 2;
            request->phase = 0x102;
        }
        func_0802D05C(state);
        break;

    case 0x103:
        request->phase = 0x105;
        if (state->status != 3)
        {
            request->phase = 0x106;
            *data_030008B0.scroll = 0x200 - state->x;
            *data_03000990.scroll = 0x200 - state->x;
        }
        func_0802D05C(state);
        break;

    case 0x102:
        func_0802D05C(state);
        break;

    case 0x106:
        state->x -= 18;
        if (state->x <= -136)
        {
            state->x = -136;
            func_0802D014(state);
            request->phase = 0x107;
        }
        state->overlay_x = state->x;
        *data_030008B0.scroll = 0x200 - state->x;
        *data_03000990.scroll = 0x200 - state->x;
        break;

    case 0x107:
        *data_030008B0.scroll = 0;
        *data_03000990.scroll = 0;
        request->phase = 0x105;
        state->status = 3;
        break;

    case 0x104:
        state->context = request->context;
        state->flags = request->flags;
        state->x = -136;
        state->y = 13;
        state->overlay_x = -136;
        state->overlay_y = 152;
        state->resource = 0;
        func_0801E458(2, 1, 0, 0, 0, data_06008000, data_0600E000);
        func_0801E458(3, 1, 1, 0, 0, data_06008000, data_06005000);
        g_control_flags_03000940 |= 0xC00;
        *data_030008B0.scroll = 0x200 - state->x;
        *data_03000990.scroll = 0x200 - state->x;
        state->status = 1;
        break;

    case 0x108:
        if (!(state->status & 0x10))
        {
            func_0802CEAC(state);
            state->status |= 0x10;
        }
        func_0802D05C(state);
        request->phase = 0x105;
        break;

    case 0x109:
        if (state->status != 2)
        {
            func_0802CFB0(state);
            state->status = 2;
        }
        func_0802D05C(state);
        request->phase = 0x102;
        break;
    }
    return 0;
}
