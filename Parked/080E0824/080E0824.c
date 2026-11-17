#include "ffta.h"
#include "control_flags.h"

// Complete target [0x080E0824, 0x080E0A8C), 616 bytes.

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u16 phase;
    u8 unknown_02[6];
    u32 mode;
} Command080E0824;

typedef struct {
    void *effect;
    u8 mode;
    u8 unknown_05;
    u16 color;
    u8 first;
    u8 second;
    u8 unknown_0A[2];
    u16 *palette;
    LineState first_line;
    LineState second_line;
} State080E0824;

typedef struct RequestNode RequestNode;

extern u16 data_03003860[];
extern u16 data_03003862[];
extern u8 data_06005800[];
extern u8 data_06008000[];
extern u8 data_0600FFA0[];

extern u16 *func_080D3904(void);
extern RequestNode *func_080D3AF8(void);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);
extern void *func_08147D94(u16 first_color, u16 mask, u8 speed,
                           u16 value, u8 first, u8 second);
extern void func_08003620(u8 value);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern u16 func_080035F8(u8 index);
extern u16 func_080035A8(u8 index);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);
extern u32 func_081485D4(void *effect);
extern void func_08148498(void *effect);
extern void func_0801DD00(u16 *count, s16 *x, s16 *y, u16 **source);
extern void func_0801DD34(u16 count, s16 x, s16 y, u16 *palette);
extern u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode);
extern void func_0801DA10(void);
extern void func_080D3A14(void);

u32 func_080E0824(void *task, Command080E0824 *command, State080E0824 *state)
{
    switch (command->phase) {
    case 0: {
        u16 *buffer = func_080D3904();

        state->mode = command->mode;
        func_0814186C(data_03003862, buffer, 0x5F);
        state->palette = buffer + 0x60;
        break;
    }
    case 0x100: {
        u16 tile;

        func_08000B68(func_080D3AF8(), -1, (u32)data_0600FFA0, 8);
        tile = 0x63FD;
        func_08000B20(func_080D3AF8(), tile, (u32)data_06005800, 0x400);
        command->phase++;
        break;
    }
    case 0x101:
        state->color = 0;
        state->first = 8;
        state->second = 8;
        state->effect = func_08147D94(1, 0x5F, 0x14, state->color, 8, 8);
        if (state->mode == 1) {
            data_03003860[0x6F] = state->color;
            func_08003620(0);
            func_080034B8(func_08003A74((u32)data_06005800) |
                          func_08003A80((u32)data_06008000) | 3, 2);
            func_08003508(0, 2);
            func_08003558(0, 2);
            g_control_flags_03000940.bldcnt_lo = 0x40 | func_080035F8(2);
            g_control_flags_03000940.bldcnt_hi = 0x20;
            g_control_flags_03000940.bldalpha_lo = 0;
            g_control_flags_03000940.bldalpha_hi = 0x10;
            g_control_flags_03000940.display |= func_080035A8(2);
            func_080075CC(&state->first_line, 0, 0, state->first, 0x14);
            func_080075CC(&state->second_line, 0x10, 0, state->second, 0x14);
        }
        command->phase++;
        break;
    case 0x102:
        if (state->mode == 1) {
            func_080076A0(&state->first_line);
            func_080076A0(&state->second_line);
            g_control_flags_03000940.bldalpha_lo = state->first_line.x;
            g_control_flags_03000940.bldalpha_hi = state->second_line.x;
            if (!func_08007880(&state->first_line))
                break;
            if (!func_08007880(&state->second_line))
                break;
        }
        if (!func_081485D4(state->effect))
            break;
        func_08148498(state->effect);
        state->effect = 0;
        if (state->mode == 1) {
            u16 count;
            s16 x;
            s16 y;
            u16 *source;
            u16 i;

            func_0801DD00(&count, &x, &y, &source);
            func_0814186C(source, state->palette, count);
            for (i = 0; i < count; i++)
                state->palette[i] = func_08147830(state->palette[i],
                    state->color, state->first, state->second);
            func_0801DD34(count, x, y, state->palette);
            func_0801DA10();
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.display &= ~func_080035A8(2);
        }
        func_080D3A14();
        command->phase = 2;
        break;
    }
    return 0;
}
