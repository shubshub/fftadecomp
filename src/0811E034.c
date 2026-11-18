// Target: complete [0x0811E034, 0x0811E1F8), 452 bytes.
#include "control_flags.h"

typedef struct Object Object;

typedef struct {
    u16 state;
    u8 unknown02[2];
    Object *object;
} Event;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u8 unknown06[2];
    void *task;
    Object *object;
    void *effect;
    void *output;
    void *handle18;
    void *handle1C;
    u32 handle20;
    void *handle24;
} Context;

typedef struct {
    u8 unknown00[4];
    Object *object;
    u8 unknown08[0xC];
    u16 selector;
    u16 option;
    u8 unknown18[4];
} Descriptor;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

struct Data;
struct Task;
extern const struct Data data_083A72D0;
extern const u8 data_083A72F4[];
extern const u8 data_083A730C[];
extern const u8 data_088F46CC[];
extern u8 data_0894C6A8[];
extern const u8 data_0894D69C[];
extern u8 data_03003920[];

extern u16 func_080035A8(u8);
extern u16 func_080035D0(u8);
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void func_080D35D8(void);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void func_080D4020(void);
extern void *func_080D4704(void *, void *);
extern void *func_080D4774(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080D6134(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern struct Task *func_080D7A70(const struct Data *, u8, struct Task *);
extern u32 func_080D7ABC(u32);
extern void func_080DBDC8(const Object *, s16 *, s16 *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080E051C(void *);
extern u32 func_080E9554(void *, void *, void *);
extern void func_0814186C(const void *, void *, u32);

u32 func_0811E034(void *owner, void *descriptor, void *payload)
{
    Event *event = descriptor;
    Context *context = payload;

    switch (event->state) {
    case 0:
    {
        context->object = event->object;
        func_080DBDC8(context->object, &context->x, &context->y);
        context->handle20 = (u32)func_080D7A70(&data_083A72D0, 3, owner);
        {
            volatile u16 fill = 0x7FFF;
            func_0814186C((const void *)&fill, data_03003920, 0x01000010);
        }
        break;
    }
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        context->handle20 = func_080D7ABC(context->handle20);
        if (context->handle20 == 0) {
            Descriptor descriptor;
            descriptor.selector = 0x18C;
            descriptor.option = 0;
            descriptor.object = context->object;
            context->task = func_08005B6C(func_080E9554, 0x70, &descriptor, owner);
            context->handle24 = func_080DFD8C(data_083A730C, 1, 4, 0, owner);
            context->timer = 20;
            event->state++;
        }
        break;
    case 0x101:
        context->task = func_080E051C(context->task);
        if (context->task == 0) {
            if (context->timer != 0 && --context->timer != 0)
                break;
            context->effect = func_080D6098(context->x, context->y, 0, 1, 1,
                &context->output, data_083A72F4, owner);
            g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
            g_control_flags_03000940.winout_hi = 0x3F;
            g_control_flags_03000940.display |= 0x8000;
            func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
            context->handle1C = func_080D4704(data_0894C6A8, owner);
            context->handle18 = func_080D3E9C(data_0894D69C, owner);
            event->state++;
        }
        break;
    case 0x102:
        context->handle18 = func_080D3F08(context->handle18);
        if (context->handle18 == 0) {
            context->handle1C = func_080D4774(context->handle1C);
            if (context->handle1C == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(2);
                func_080D4020();
                g_control_flags_03000940.display &= 0x7FFF;
                context->effect = func_080D6134(context->effect);
                if (context->effect == 0)
                    event->state = 2;
            }
        }
        break;
    }
    return 0;
}
