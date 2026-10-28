#include "ffta.h"

typedef struct {
    void *resource;
    s16 x;
    s16 y;
    u16 attributes;
    u8 priority;
    u8 mode;
    u8 active;
    u8 unknown_0d[3];
} Sprite;

typedef struct {
    u32 unknown_00[2];
    s16 x;
    u16 unknown_0a;
} Target;

typedef struct {
    s32 limit;
    s32 velocity;
    s32 unknown_08;
    s32 position;
    s32 acceleration;
    s8 stop_at_turn;
    u8 unknown_15[3];
} Motion;

typedef struct {
    void *first;
    void *second;
    Target *targets;
    Sprite sprites[15];
    Motion horizontal[15];
    Motion vertical[15];
    void *effect1;
    void *effect2;
    u8 fade_ticks;
    u8 effect_stage;
    u8 unknown_3d6[2];
    s8 wait_ticks;
    u8 unknown_3d9[0x57];
    u16 state;
} Context;

typedef struct {
    u16 flags;
    u8 unknown_02[0x48];
    u8 window_inside : 8;
    u8 window_outside : 8;
    u8 blend_a : 8;
    u8 blend_b : 8;
} Display;

typedef struct {
    u32 unknown_00[5];
    void *buffer;
} Buffer;

extern s8 data_0200F498;
extern s8 data_0200F49C;
extern s8 data_0200F4A0;
extern s8 data_0200F4A4;
extern u8 data_0200F47C[];
extern Buffer data_030008B0;
extern Display g_control_flags_03000940;

extern void func_08022854(void *);
extern void func_08141748(u16);
extern void *func_080CBABC(u8);
extern void *func_08147D2C(int, int, int, void *);
extern void func_081416DC(u16);
extern int func_081485D4(void *);
extern void *func_081484CC(void *);
extern u8 func_08090264(Motion *);
extern u16 func_08002804(void);
extern void func_08000B20(void *, u16, void *, u16);
extern void func_08001F34(void *, int, int, u8, u8, u8, u8, u8,
                         u32, u8, const void *);

/* Complete [0x08090F70, 0x080917F6): 2182 bytes, 941 instructions. */
int func_08090F70(Context *ctx)
{
    int i;
    int distance;
    int step;
    int moving;
    int blend;

    switch (ctx->state) {
    case 0:
        func_08022854(ctx->first);
        func_08022854(ctx->second);
        ctx->first = 0;
        ctx->second = 0;
        func_08141748(4);
        ctx->wait_ticks = 0;
        ctx->state = 1;
        break;
    case 1:
        if (ctx->wait_ticks <= 59) {
            ctx->wait_ticks++;
            break;
        }
        ctx->wait_ticks = 0;
        ctx->state = 2;
        break;
    case 2:
        if (ctx->wait_ticks <= 23) {
            ctx->wait_ticks++;
            break;
        }
        ctx->wait_ticks = 0;
        g_control_flags_03000940.window_inside = 0x40;
        g_control_flags_03000940.window_outside = 0x3f;
        g_control_flags_03000940.blend_a = 0;
        g_control_flags_03000940.blend_b = 16;
        for (i = 0; i < data_0200F498; i++) {
            Sprite *sprite = &ctx->sprites[i];
            Motion *vertical = &ctx->vertical[i];
            Motion *horizontal = &ctx->horizontal[i];
            double speed;

            horizontal->limit = (int)((data_0200F4A0 * 8 - 16) * 256.0);
            speed = i + 1;
            horizontal->velocity = (int)((speed + speed) * 256.0);
            horizontal->position = (int)((data_0200F4A0 * 8 + i * 4) * 256.0);
            horizontal->acceleration = (int)(speed * -0.05 * 256.0);
            horizontal->stop_at_turn = 0;
            vertical->limit = (int)((data_0200F4A4 * 8) * 256.0);
            vertical->velocity = -1536;
            vertical->position = (int)((data_0200F4A4 * 8 - i * 6) * 256.0);
            vertical->acceleration = 179;
            vertical->stop_at_turn = 0;
            sprite->x = horizontal->position >> 8;
            sprite->y = vertical->position >> 8;
            sprite->active = 1;
            sprite->priority = 1;
        }
        ctx->fade_ticks = 0;
        ctx->effect1 = func_08147D2C(352, 16, 64, func_080CBABC(14));
        func_081416DC(6);
        ctx->state = 3;
        break;
    case 3:
        moving = 0;
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            g_control_flags_03000940.blend_a = ctx->fade_ticks;
            g_control_flags_03000940.blend_b = 16 - ctx->fade_ticks;
        }
        for (i = 0; i < data_0200F498; i++) {
            Sprite *sprite = &ctx->sprites[i];
            Motion *vertical = &ctx->vertical[i];
            Motion *horizontal = &ctx->horizontal[i];
            if (func_08090264(horizontal))
                moving = 1;
            if (!func_08090264(vertical)) {
                ctx->vertical[i].velocity = -ctx->vertical[i].velocity + ctx->vertical[i].velocity / 4;
                {
                    int velocity = ctx->vertical[i].velocity;
                    if (velocity < 0)
                        velocity = -velocity;
                    if (velocity <= 511)
                        ctx->vertical[i].velocity = 0;
                }
            }
            sprite->x = horizontal->position >> 8;
            sprite->y = vertical->position >> 8;
            if (ctx->fade_ticks > 15)
                sprite->priority = 0;
        }
        if (moving)
            break;
        for (i = 0; i < data_0200F49C; i++)
            ctx->sprites[i].y = data_0200F4A4 * 8;
        for (i = data_0200F498; i < data_0200F49C; i++) {
            ctx->sprites[i].x = data_0200F4A0 * 8 + ctx->targets[i].x;
            ctx->sprites[i].active = 1;
            ctx->sprites[i].priority = 1;
        }
        if (!func_081485D4(ctx->effect1))
            break;
        func_081484CC(ctx->effect1);
        g_control_flags_03000940.blend_a = 0;
        g_control_flags_03000940.blend_b = 16;
        ctx->fade_ticks = 0;
        ctx->effect_stage = 0;
        ctx->state = 4;
        break;
    case 4:
        moving = 0;
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            g_control_flags_03000940.blend_a = ctx->fade_ticks;
            g_control_flags_03000940.blend_b = 16 - ctx->fade_ticks;
        }
        for (i = 0; i < data_0200F498; i++) {
            distance = data_0200F4A0 * 8 + ctx->targets[i].x - ctx->sprites[i].x;
            step = distance / 4;
            if (distance) {
                moving = 1;
                if (!step)
                    step = distance / (distance < 0 ? -distance : distance);
                ctx->sprites[i].x += step;
            }
        }
        if (moving)
            break;
        g_control_flags_03000940.flags |= 0x400;
        g_control_flags_03000940.window_inside = 0x44;
        g_control_flags_03000940.window_outside = 0x3b;
        g_control_flags_03000940.blend_a = 0;
        g_control_flags_03000940.blend_b = 16;
        ctx->fade_ticks = 0;
        for (i = 0; i < data_0200F49C; i++)
            ctx->sprites[i].priority = 0;
        ctx->effect1 = func_08147D2C(352, 16, 32, func_080CBABC(15));
        ctx->effect2 = func_08147D2C(96, 16, 32, func_080CBABC(15));
        ctx->effect_stage = 1;
        ctx->state = 5;
        break;
    case 5:
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            blend = ctx->fade_ticks;
            if (blend > 16)
                blend = 16;
            g_control_flags_03000940.blend_a = blend;
            blend = 16 - ctx->fade_ticks;
            if (blend <= 12)
                blend = 13;
            g_control_flags_03000940.blend_b = blend;
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
            ctx->effect1 = func_08147D2C(352, 16, 32, func_080CBABC(14));
            ctx->effect2 = func_08147D2C(96, 16, 32, func_080CBABC(14));
            ctx->effect_stage++;
            break;
        default:
            ctx->fade_ticks = 0;
            ctx->state = 6;
        }
        break;
    case 6:
        if (++ctx->fade_ticks <= 47)
            break;
        ctx->fade_ticks = 0;
        ctx->state = 7;
        break;
    case 7:
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            g_control_flags_03000940.blend_a = 16 - ctx->fade_ticks;
            break;
        }
        g_control_flags_03000940.flags &= 0xfbff;
        func_08000B20(data_0200F47C, 0, data_030008B0.buffer, 0x400);
        for (i = 0; i < data_0200F49C; i++)
            ctx->sprites[i].priority = 1;
        g_control_flags_03000940.window_inside = 0x40;
        g_control_flags_03000940.window_outside = 0x3f;
        g_control_flags_03000940.blend_a = 16;
        g_control_flags_03000940.blend_b = 0;
        ctx->fade_ticks = 0;
        for (i = 0; i < data_0200F49C; i++) {
            Sprite *sprite = &ctx->sprites[i];
            Motion *vertical = &ctx->vertical[i];
            vertical->limit = 0xa000;
            vertical->velocity = (int)(-(s16)((s16)func_08002804() % 5) * 256.0);
            vertical->position = (int)((data_0200F4A4 * 8) * 256.0);
            vertical->acceleration = 179;
            vertical->stop_at_turn = 0;
            sprite->y = vertical->position >> 8;
            sprite->active = 1;
            sprite->priority = 1;
        }
        ctx->state = 8;
        break;
    case 8:
        for (i = 0; i < data_0200F49C; i++) {
            Sprite *sprite = &ctx->sprites[i];
            Motion *vertical = &ctx->vertical[i];
            func_08090264(vertical);
            if (i < data_0200F49C / 2)
                sprite->x--;
            else
                sprite->x++;
            sprite->y = vertical->position >> 8;
        }
        if (ctx->fade_ticks <= 15) {
            ctx->fade_ticks++;
            g_control_flags_03000940.blend_a = 16 - ctx->fade_ticks;
            g_control_flags_03000940.blend_b = ctx->fade_ticks;
        } else {
            ctx->state = 9;
        }
        break;
    case 9:
        return 0;
    }

    for (i = 0; i < 15; i++) {
        if (ctx->sprites[0].y > 159)
            ctx->sprites[0].y = 160;
        if (ctx->sprites[i].active)
            func_08001F34(ctx->sprites[i].resource, ctx->sprites[i].x,
                         ctx->sprites[i].y, ctx->sprites[i].priority,
                         0, 0, 0, 0, ctx->sprites[i].attributes, 0,
                         (const void *)(u32)ctx->sprites[i].mode);
    }
    return 1;
}
