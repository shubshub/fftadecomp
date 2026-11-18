#include "ffta.h"
#include "effect_task.h"

// Target: complete [0x08101410, 0x0810163C), 556 bytes, 278 instructions.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 variant;
} Descriptor08101410;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 variant;
    u8 status;
    u8 flag;
    u8 unknown_09[3];
    void *child;
    void *object;
    void *coordinate_result;
    void *actor;
    void *stage;
    u8 unknown_20[8];
    void *coordinate_task;
    void *actor_task;
    void *record_task;
} Payload08101410;

typedef struct {
    u8 unknown_00[14];
    u16 kind;
} ActorObject08101410;

typedef struct {
    u32 unknown_00;
    void *actor;
    u8 *status;
    u8 unknown_0c[8];
    u16 flag;
    u8 unknown_16[6];
} ChildDescriptor08101410;

extern const u8 data_0839EAD4[];
extern const u8 data_0839EB04[];
extern const u8 data_0839EB34[];
extern const u8 data_0839EB50[];

extern u32 func_08100EF0(void *, void *, void *);
extern void *func_08005B6C(u32 (*)(void *, void *, void *), u16, void *, void *);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern ActorObject08101410 *func_080DD4A4(void *, u8);
extern void *func_080DD47C(void *);
extern void func_080DE10C(void *, u16);
extern void func_080DE390(void *);
extern u8 func_080D8858(void *, u8);
extern void func_080DBD78(void *, s16 *, s16 *, s16 *);
extern void *func_080DFA30(void *, u16, u8, u8, u8, u16, void *);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);

extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080E051C(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08101410(void *task, Descriptor08101410 *descriptor,
                  Payload08101410 *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u8 mode;

        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->variant)
            mode = 0;
        payload->stage = func_080E03F8(payload->actor, data_0839EAD4,
                                       mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
    {
        ChildDescriptor08101410 child;

        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        if (func_080DD4A4(payload->actor, 0)->kind == 6)
            payload->flag = 1;
        child.flag = payload->flag;
        child.actor = payload->actor;
        child.status = &payload->status;
        payload->child = func_08005B6C(func_08100EF0, 0x90, &child, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (payload->status != 1)
            break;
        payload->object = func_080DD47C(payload->actor);
        func_080DE10C(payload->object, 0x8C);
        payload->countdown = 0x10;
        descriptor->phase++;
        break;
    case 0x102:
        if (--payload->countdown != 0)
            break;
        payload->status = 2;
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->status != 3)
            break;
        func_080DE390(payload->object);
        descriptor->phase++;
        break;
    case 0x104:
    {
        ActorObject08101410 *object;

        if (payload->status != 4)
            break;
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        if (payload->flag) {
            s16 x, y, z;

            func_080DBD78(payload->object, &x, &y, &z);
            payload->actor_task = func_080DFA30(object, 0x3D1, 6, x, z,
                                                0, task);
        } else {
            payload->coordinate_result = func_080DD748(object, &payload->x,
                                                       &payload->y, 0);
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 2, payload->unknown_20, data_0839EB04, task);
            payload->actor_task = func_080DCFE4(object, data_0839EB34,
                12, 20, 4, task, 20);
            payload->record_task = func_080DFD8C(data_0839EB50, 1, 4, 0,
                                                 task);
        }
        descriptor->phase++;
        break;
    }
    case 0x105:
        payload->child = func_080E051C(payload->child);
        if (payload->child)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        payload->actor_task = func_080DBA5C(payload->actor_task);
        if (!payload->actor_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
