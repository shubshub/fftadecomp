#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} PanelContext;

typedef struct {
    u16 phase;
    u16 unknown_02;
    PanelContext *context;
    u8 unknown_08[0x0C];
    u16 selection;
} PanelRequest;

typedef struct {
    u16 x;
    u16 width;
} AnimationBand;

typedef struct {
    u8 unknown_00[0x1C];
} TransferRequest;

typedef struct {
    PanelContext *context;
    u8 mode;
    u8 palette;
    u8 selection;
    u8 unknown_07;
    u16 timer;
    u16 unknown_0A;
    AnimationBand first;
    AnimationBand second;
    void *effect;
    u8 text[0x290];
    void *graphics;
    void *text_buffer;
    u8 icon[0x80];
    u16 tilemap[28];
    TransferRequest transfers[6];
} PanelState;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} SystemState;

typedef struct {
    u8 unknown_00[0xB2];
    u8 selection;
    u8 unknown_0B3[0x1AA5];
    u16 selection_mode;
} GameState;

typedef struct {
    u16 control;
    u8 unknown_02[0x48];
    u32 blend_low : 8;
    u32 blend_high : 8;
    u32 alpha_a : 8;
    u32 alpha_b : 8;
    u32 brightness : 8;
} DisplayShadow;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u8 *map;
} Background;

typedef struct {
    u16 unknown_00;
    u16 pressed;
} InputState;

typedef void (*ClearFunction)(void *destination, u32 size);
typedef void (*CopyFunction)(void *destination, const void *source, u32 size);

extern SystemState g_state_0200F390;
extern GameState g_state_020020D0;
extern DisplayShadow g_control_flags_03000940;
extern Background data_030008B0;
extern Background data_03000990;
extern InputState data_03000000;
extern u8 data_03003920[];
extern const u8 data_083C11BC[];
extern const u8 data_083C15B4[];
extern const u8 data_083C16F4[];
extern ClearFunction g_callbacks_0836D4B8[];
extern CopyFunction data_0836D4BC[];

extern void *func_08121B64(u32 size);
extern void func_08121B78(void *allocation);
extern void func_0800C6C0(void *effect);
extern void func_0800C668(void *effect);
extern const void *func_080CBABC(u32 index);
extern void func_0800543C(void *destination, const void *source);
extern const void *func_080CEB34(u8 selection);
extern u32 func_080CEBF8(u8 selection);
extern void func_080CB9B0(void *destination, u8 job);
extern u32 func_080CB9CC(u8 job);
extern void func_08015110(void *state, void *buffer, const void *text,
                         u32 zero, u32 enabled);
extern void func_080157A8(u16 *tilemap, u32 x, u32 y, u32 width,
                         u32 height, u32 stride, u32 tile, u8 palette);
extern void *func_0800D61C(u32 type, u32 count);
extern void func_0800DAB8(void *effect, u8 first, u8 second,
                         u8 alpha_a, u8 alpha_b);
extern void func_0800DB0C(void *effect, s16 position, u8 width,
                         u32 first, u32 second, u32 third, u32 fourth);
extern void func_08000ADC(void *request, const void *source,
                         void *destination, u32 words);
extern void func_08000B20(TransferRequest *request, u32 fill,
                         void *destination, u32 count);
extern void func_08000B68(TransferRequest *request, u32 fill,
                         void *destination, u32 count);
extern void func_08000BAC(TransferRequest *request, const void *source,
                         void *destination, u16 width, u16 height,
                         u16 source_stride, u16 destination_stride);

/* Target [0x0812803C, 0x081286DA): 1694 bytes, 732 instructions. */
u32 func_0812803C(void *unused, PanelRequest *request, PanelState *state)
{
    u16 aborted = g_state_0200F390.flags & 0x400;

    if (aborted)
    {
        if (state->effect)
        {
            func_0800C6C0(state->effect);
            func_0800C668(state->effect);
            state->effect = 0;
        }
        return 0;
    }

    switch (request->phase)
    {
    case 1:
        if (state->graphics)
        {
            func_08121B78(state->graphics);
            state->graphics = 0;
        }
        if (state->text_buffer)
        {
            func_08121B78(state->text_buffer);
            state->text_buffer = 0;
        }
        break;

    case 0:
        state->context = request->context;
        state->selection = request->selection;
        g_state_020020D0.selection = state->selection;
        state->graphics = func_08121B64(0xA80);
        state->text_buffer = func_08121B64(0x2C0);
        g_callbacks_0836D4B8[0](state->text_buffer, 4);
        g_callbacks_0836D4B8[0](state->tilemap, 0x38);
        if (state->selection == 0)
            state->mode = g_state_020020D0.selection_mode == 0;
        else
            state->mode = state->selection != 1;
        data_0836D4BC[0](data_03003920, func_080CBABC(8), 0x40);
        break;

    case 0x100:
        func_08000B20(&state->transfers[5], 0,
                     data_030008B0.map + 0x290, 0x40);
        request->phase = 0x101;
        break;

    case 0x101:
    {
        u8 job;

        func_0800543C(state->graphics, data_083C11BC);
        func_08015110(state->text, state->text_buffer,
                     func_080CEB34(state->selection), 0, 1);
        job = func_080CEBF8(state->selection);
        func_080CB9B0(state->icon, job);
        state->palette = func_080CB9CC(job);
        g_control_flags_03000940.blend_low = 0x4C;
        g_control_flags_03000940.blend_high = 0x33;
        g_control_flags_03000940.alpha_a = 0;
        g_control_flags_03000940.alpha_b = 16;
        g_control_flags_03000940.brightness = 0;
        g_control_flags_03000940.control =
            (g_control_flags_03000940.control & ~0x400) | 0x800;
        request->phase = 0x102;
        break;
    }

    case 0x102:
        func_08000ADC(&state->transfers[0], state->graphics,
                     data_03000990.tiles + 0x1C00, 0x2A0);
        request->phase = 0x103;
        break;

    case 0x103:
        func_08000ADC(&state->transfers[1], state->text_buffer,
                     data_030008B0.tiles + 0x2680, 0xB0);
        func_08000ADC(&state->transfers[2], state->icon,
                     data_030008B0.tiles + 0x2940, 0x20);
        request->phase = 0x104;
        break;

    case 0x104:
    {
        u16 *tilemap = state->tilemap;

        func_080157A8(&state->tilemap[3], 0, 0, 11, 1, 14,
                     0x134, state->mode + 6);
        tilemap[0] = (state->palette << 12) + 0x14A;
        tilemap[1] = (state->palette << 12) + 0x14B;
        tilemap[14] = (state->palette << 12) + 0x14C;
        tilemap[15] = (state->palette << 12) + 0x14D;
        func_08000BAC(&state->transfers[3],
                     state->mode ? data_083C16F4 : data_083C15B4,
                     data_03000990.map + 0x18A, 20, 8, 40, 64);
        func_08000BAC(&state->transfers[4], tilemap,
                     data_030008B0.map + 0x290, 14, 2, 28, 64);
        state->effect = func_0800D61C(0, 16);
        g_callbacks_0836D4B8[0](&state->first, 8);
        state->timer = 0x80;
        request->phase = 0x105;
        break;
    }

    case 0x105:
    {
        AnimationBand *first = &state->first;
        AnimationBand *second = &state->second;

        first->x--;
        if ((s16)first->x > -48)
        {
            s32 width = (s16)first->x;

            if (width < 0)
                width = -width;
            if (width > 20)
                width = 20;
            first->width = width;
            func_0800DB0C(state->effect, first->x + 80, width,
                         0, 16, 16, 0);
            if (second->width < 20)
                second->width++;
            else
            {
                second->width = 20;
                second->x++;
            }
            func_0800DB0C(state->effect, second->x + 80, second->width,
                         0, 0, 0, 16);
        }
        else
        {
            first->x = 0;
            first->width = 0;
            g_control_flags_03000940.blend_low = 0x44;
            g_control_flags_03000940.blend_high = 0x3B;
            func_0800DAB8(state->effect, 48, 64, first->x, 16 - first->x);
            g_control_flags_03000940.control |= 0x400;
            request->phase = 0x106;
        }
        break;
    }

    case 0x106:
        if (state->first.x != 16)
        {
            state->first.x += 2;
            func_0800DAB8(state->effect, 48, 64,
                         state->first.x, 16 - state->first.x);
        }
        else
            request->phase = 0x107;
        break;

    case 0x107:
        if (state->timer)
            state->timer--;
        if (state->timer <= 95 && (data_03000000.pressed & 1))
            state->timer = 0;
        if (state->timer == 0)
            request->phase = 0x108;
        break;

    case 0x108:
    {
        AnimationBand *first = &state->first;

        if (first->x != 0)
        {
            first->x -= 2;
            func_0800DAB8(state->effect, 48, 64, first->x, 16 - first->x);
        }
        else
        {
            g_control_flags_03000940.control &= ~0x400;
            g_control_flags_03000940.blend_low = 0x4C;
            g_control_flags_03000940.blend_high = 0x33;
            first->x = 32;
            first->width = 20;
            state->second.x = 112;
            state->second.width = 20;
            func_0800DAB8(state->effect, 48, 64, 16, 0);
            request->phase = 0x109;
        }
        break;
    }

    case 0x109:
    {
        AnimationBand *first = &state->first;
        AnimationBand *second = &state->second;

        if ((s16)first->x < 80)
        {
            first->x++;
            if (80 - (s16)first->x < 20)
                first->width--;
            if ((s16)second->x > 80)
                second->x--;
            else
                second->width--;
            if (first->width)
                func_0800DB0C(state->effect, first->x, first->width,
                             0, 16, 16, 0);
            if (second->width)
                func_0800DB0C(state->effect, second->x, second->width,
                             0, 0, 0, 16);
        }
        else
        {
            func_0800DAB8(state->effect, 48, 64, 0, 16);
            request->phase = 0x10A;
        }
        break;
    }

    case 0x10A:
        func_08121B78(state->graphics);
        state->graphics = 0;
        func_08121B78(state->text_buffer);
        state->text_buffer = 0;
        func_08000B20(&state->transfers[0], 0,
                     data_03000990.map + 0x18A, 0x100);
        func_08000B20(&state->transfers[1], 0,
                     data_030008B0.map + 0x290, 0x40);
        state->timer = 0;
        request->phase = 0x10B;
        break;

    case 0x10B:
        state->timer++;
        if (state->timer == 1)
        {
            func_08000B68(&state->transfers[2], 0,
                         data_03000990.tiles + 0x1C00, 0x2A0);
            func_08000B68(&state->transfers[3], 0,
                         data_030008B0.tiles + 0x2680, 0xD0);
            func_0800C6C0(state->effect);
        }
        else if (state->timer > 7)
        {
            func_0800C668(state->effect);
            g_control_flags_03000940.blend_low = 0;
            g_control_flags_03000940.blend_high = 0;
            g_control_flags_03000940.alpha_a = 0;
            g_control_flags_03000940.alpha_b = 0;
            g_control_flags_03000940.control |= 0x400;
            state->timer = 0;
            request->phase = 0x10C;
        }
        break;

    case 0x10C:
        state->context->complete = 1;
        request->phase = 3;
        break;
    }
    return 0;
}
