#include "ffta.h"

struct Sprite080902CC {
    void *resource;
    s16 x;
    s16 y;
    u16 attributes;
    u8 priority;
    u8 mode;
    u8 active;
    u8 unknown_0d[3];
};

struct Target080902CC {
    u32 unknown_00[2];
    s16 x;
    u16 unknown_0a;
};

struct Motion080902CC {
    s32 unknown_00;
    s32 velocity;
    s32 unknown_08;
    s32 position;
    s32 unknown_10[2];
};

struct Context080902CC {
    void *first;
    void *second;
    struct Target080902CC *targets;
    struct Sprite080902CC sprites[14];
    struct Motion080902CC motion[14];
    s8 wait_ticks;
    u8 unknown_23d[3];
    s8 left_index;
    s8 right_index;
    u8 fade_ticks;
    u8 fade_step_ticks;
    u8 effect_stage;
    u8 unknown_245[3];
    void *effect1;
    void *effect2;
    u8 unknown_250[0x54];
    u16 state;
};

struct Display080902CC {
    u16 flags;
    u8 unknown_02[0x48];
    u16 window_inside : 8;
    u16 window_outside : 8;
    u16 blend_a : 8;
    u16 blend_b : 8;
};

struct Buffer080902CC {
    u32 unknown_00[5];
    void *buffer;
};

extern s8 data_0200F498;
extern s8 data_0200F49C;
extern s8 data_0200F4A0;
extern s8 data_0200F4A4;
extern u8 data_0200F47C[];
extern struct Buffer080902CC data_030008B0;
extern struct Display080902CC g_control_flags_03000940;

extern void func_08022854(void *);
extern void func_08141748(int);
extern void *func_080CBABC(int);
extern void *func_08147D2C(int, int, int, void *);
extern void func_081416DC(void);
extern int func_081485D4(void *);
extern void func_081484CC(void *);
extern u16 func_08002804(void);
extern void func_08000B20(void *, int, void *, int);
extern void func_08001F34(void *, int, int, int, int, int, int, int,
                         int, int, int);

/* Target: [0x080902CC, 0x08090A80), 1972 bytes, 847 instructions. */
int func_080902CC(struct Context080902CC *ctx)
{
    int i;
    int distance;
    int step;
    int moving;
    int blend;
    int amount;
    int coordinate;

    switch (ctx->state) {
    case 0:
        func_08022854(ctx->first);
        func_08022854(ctx->second);
        ctx->first = 0;
        ctx->second = 0;
        func_08141748(4);
        ctx->state = 1;
        break;
    case 1:
        if (ctx->wait_ticks > 59) {
            ctx->wait_ticks = 0;
            ctx->state = 2;
        } else {
            ctx->wait_ticks++;
        }
        break;
    case 2:
        if (ctx->wait_ticks <= 23) {
            ctx->wait_ticks++;
            break;
        }
        ctx->wait_ticks = 0;
        for (i = 0; i < data_0200F498; i++) {
            ctx->sprites[i].x = -32;
            ctx->sprites[i].y = data_0200F4A4 * 8;
            ctx->sprites[i].active = 1;
            ctx->sprites[i].priority = 0;
        }
        for (i = data_0200F498; i < data_0200F49C; i++) {
            ctx->sprites[i].x = 272;
            ctx->sprites[i].y = data_0200F4A4 * 8;
            ctx->sprites[i].active = 1;
            ctx->sprites[i].priority = 0;
        }
        ctx->right_index = data_0200F498;
        ctx->effect1 = func_08147D2C(352, 16, 128, func_080CBABC(16));
        ctx->left_index = data_0200F498 - 1;
        ctx->state = 3;
        func_081416DC();
        break;
    case 3:
        i = ctx->left_index;
        moving = 0;
        distance = data_0200F4A0 * 8 + ctx->targets[i].x - ctx->sprites[i].x;
        step = distance / (data_0200F498 - i + 4);
        if (step == 0)
            step = distance / (distance < 0 ? -distance : distance);
        ctx->sprites[i].x += step;
        if (distance == 0 && ctx->left_index >= 0)
            ctx->left_index--;
        if (ctx->left_index >= 0)
            moving = 1;

        i = ctx->right_index;
        distance = data_0200F4A0 * 8 + ctx->targets[i].x - ctx->sprites[i].x;
        step = distance / (i - data_0200F498 + 4);
        if (step == 0)
            step = distance / (distance < 0 ? -distance : distance);
        ctx->sprites[i].x += step;
        if (distance == 0 && ctx->right_index < data_0200F49C)
            ctx->right_index++;
        if (ctx->right_index < data_0200F49C)
            moving = 1;
        if (moving)
            break;

        g_control_flags_03000940.flags |= 0x400;
        g_control_flags_03000940.window_inside = 0x44;
        g_control_flags_03000940.window_outside = 0x3b;
        g_control_flags_03000940.blend_a = 0;
        g_control_flags_03000940.blend_b = 16;
        ctx->fade_ticks = 0;
        if (!func_081485D4(ctx->effect1))
            break;
        func_081484CC(ctx->effect1);
        ctx->effect_stage = 1;
        ctx->effect1 = func_08147D2C(352, 16, 64, func_080CBABC(17));
        ctx->effect2 = func_08147D2C(96, 16, 64, func_080CBABC(17));
        ctx->state = 4;
        break;
    case 4:
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            blend = ctx->fade_ticks;
            if (blend > 8)
                blend = 8;
            g_control_flags_03000940.blend_a = blend;
            blend = 16 - ctx->fade_ticks;
            if (blend <= 8)
                blend = 9;
            g_control_flags_03000940.blend_b = blend;
        }
        for (i = 0; i < data_0200F49C; i++) {
            ctx->sprites[i].x = data_0200F4A0 * 8 + ctx->targets[i].x;
            ctx->sprites[i].y = data_0200F4A4 * 8;
            if ((s16)((s16)func_08002804() % 101) <= 39) {
                amount = (s16)((s16)func_08002804() % 2);
                coordinate = ctx->sprites[i].x;
                if (func_08002804() & 1)
                    ctx->sprites[i].x = coordinate - amount;
                else
                    ctx->sprites[i].x = coordinate + amount;
            }
            if ((s16)((s16)func_08002804() % 101) <= 39) {
                amount = (s16)((s16)func_08002804() % 2);
                coordinate = ctx->sprites[i].y;
                if (func_08002804() & 1)
                    ctx->sprites[i].y = coordinate - amount;
                else
                    ctx->sprites[i].y = coordinate + amount;
            }
        }
        switch (ctx->effect_stage) {
        case 1:
        case 3:
            if (!func_081485D4(ctx->effect1))
                break;
            if (!func_081485D4(ctx->effect2))
                break;
            func_081484CC(ctx->effect1);
            func_081484CC(ctx->effect2);
            ctx->effect_stage++;
            break;
        case 2:
            ctx->effect1 = func_08147D2C(352, 16, 64, func_080CBABC(16));
            ctx->effect2 = func_08147D2C(96, 16, 64, func_080CBABC(16));
            ctx->effect_stage++;
            break;
        default:
            for (i = 0; i < data_0200F49C; i++) {
                ctx->sprites[i].x = data_0200F4A0 * 8 + ctx->targets[i].x;
                ctx->sprites[i].y = data_0200F4A4 * 8;
            }
            ctx->fade_ticks = 0;
            ctx->state = 5;
        }
        break;
    case 5:
        if (++ctx->fade_ticks > 199)
            ctx->state = 6;
        break;
    case 6:
        if (++ctx->fade_step_ticks <= 3)
            break;
        ctx->fade_step_ticks = 0;
        blend = g_control_flags_03000940.blend_a - 1;
        if (blend < 0)
            blend = 0;
        g_control_flags_03000940.blend_a = blend;
        if (blend != 0)
            break;
        g_control_flags_03000940.flags &= 0xfbff;
        func_08000B20(data_0200F47C, 0, data_030008B0.buffer, 0x400);
        ctx->state = 7;
        break;
    case 7:
        g_control_flags_03000940.window_inside = 0x40;
        g_control_flags_03000940.window_outside = 0x3f;
        for (i = 0; i < data_0200F49C; i++) {
            ctx->motion[i].position = (int)((double)ctx->sprites[i].y * 256.0);
            ctx->motion[i].velocity = 204 - (s16)((s16)func_08002804() % 129);
            ctx->sprites[i].priority = 1;
        }
        ctx->fade_ticks = 0;
        g_control_flags_03000940.blend_a = 16;
        g_control_flags_03000940.blend_b = 0;
        ctx->fade_step_ticks = 0;
        ctx->state = 8;
        break;
    case 8:
        if (++ctx->fade_step_ticks > 4) {
            ctx->fade_ticks++;
            ctx->fade_step_ticks = 0;
        }
        for (i = 0; i < data_0200F49C; i++) {
            ctx->motion[i].position += ctx->motion[i].velocity;
            ctx->sprites[i].y = ctx->motion[i].position >> 8;
        }
        if (ctx->fade_ticks > 16)
            return 0;
        g_control_flags_03000940.blend_a = 16 - ctx->fade_ticks;
        g_control_flags_03000940.blend_b = ctx->fade_ticks;
        break;
    }

    for (i = 0; i < 14; i++) {
        if (ctx->sprites[0].y > 159)
            ctx->sprites[0].y = 160;
        if (ctx->sprites[i].active) {
            func_08001F34(ctx->sprites[i].resource, ctx->sprites[i].x,
                         ctx->sprites[i].y, ctx->sprites[i].priority,
                         0, 0, 0, 0, ctx->sprites[i].attributes, 0,
                         ctx->sprites[i].mode);
        }
    }
    return 1;
}
