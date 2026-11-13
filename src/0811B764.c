#include "control_flags.h"

// Target: complete [0x0811B764, 0x0811B886), 290 bytes, 112 instructions.

typedef struct {
    u16 phase;
} Event;

typedef struct {
    u8 unknown_00[8];
    void *animation;
    void *overlay;
    void *fade;
    u32 palette;
} Context;

extern const u8 data_083A6AB4[];
extern const u8 data_083A6ACC[];
extern const u8 data_088F4D34[];
extern const u8 data_0894C770[];
extern const u8 data_0894D69C[];
extern u8 data_03003920[];

extern u32 func_080035A8(u8);
extern void func_080D35D8(void);
extern void func_080D3AC0(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u32 func_080D7A70(const void *, u8, void *);
extern u32 func_080D7ABC(u32);
extern void *func_080D98D4(int, int, int, int, const void *, void *);
extern void *func_080D9B64(void *);
extern void func_0814186C(const void *, void *, u32);

u32 func_0811B764(void *owner, Event *event, Context *context)
{
    switch (event->phase) {
    case 0:
    {
        u16 fill;
        context->palette = func_080D7A70(data_083A6AB4, 2, owner);
        fill = 0;
        func_0814186C(&fill, data_03003920, 0x01000010);
        break;
    }
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        context->palette = func_080D7ABC(context->palette);
        if (context->palette == 0) {
            func_080D7220(data_088F4D34, 0, 2, 0, 0, 0);
            context->overlay = func_080D4704(data_0894C770, owner);
            context->animation = func_080D3E9C(data_0894D69C, owner);
            context->fade = func_080D98D4(2, 0, 0, 0, data_083A6ACC, owner);
            event->phase++;
        }
        break;
    case 0x101:
        context->animation = func_080D3F08(context->animation);
        if (context->animation == 0) {
            context->overlay = func_080D4774(context->overlay);
            if (context->overlay == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(2);
                g_control_flags_03000940.bldcnt_lo = 0xbf;
                g_control_flags_03000940.bldy_lo = 0x10;
                func_080D3AC0(0);
                event->phase++;
            }
        }
        break;
    case 0x102:
        context->fade = func_080D9B64(context->fade);
        if (context->fade == 0)
            event->phase = 2;
        break;
    }
    return 0;
}
