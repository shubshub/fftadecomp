// Target: complete [0x080FE2E8, 0x080FE592), 682 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 mode;
} Descriptor080FE2E8;

typedef struct {
    u8 unknown_00[5];
    u8 mode;
    u8 finished;
    u8 alternate;
    u8 unknown_08[4];
    s16 from_x;
    s16 from_y;
    s16 from_z;
    u8 unknown_12[2];
    s16 to_x;
    s16 to_y;
    s16 to_z;
    u8 unknown_1a[2];
    Struct080DBD5C *object;
    Struct080DBD5C *target;
    void *actor;
    void *motion_task;
    void *child_task;
    void *effect_task;
    void *initial_task;
    void *sprite_task;
    void *sound_task;
} Payload080FE2E8;

typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *from;
    s16 *to;
    u8 unknown_0c[8];
    u16 palette;
    s16 direction;
    u8 unknown_18[4];
} MotionDescriptor080FE2E8;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[20];
} ChildDescriptor080FE2E8;

typedef struct {
    u8 unknown_00[0x14];
    u16 duration;
    u8 unknown_16[0x82];
    void *sprite;
    u8 unknown_9c[0x178];
    void *motion;
} MotionState080FE2E8;

typedef struct {
    u8 unknown_00[14];
    u16 kind;
} Target080FE2E8;

struct Data080FE2E8;
extern const struct Data080FE2E8 data_0839D844;
extern const struct Data080FE2E8 data_0839D8B8;

extern u32 func_080FDF90(void *, void *, void *);
extern u32 func_080FE234(void *, void *, void *);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void *func_080DE4B0(void *, u8 *, u8, s8, s8, u8, u32, void *);
extern u8 func_080DD494(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080D8B7C(void *, s16 *, s16 *, s16 *);
extern u8 func_080DBC88(void *);
extern u16 func_080DD488(void *);
extern void *func_08005B6C(void *, u32, void *, void *);
extern u16 func_08005BAC(void *);
extern Target080FE2E8 *func_080DD4A4(void *, u8);
extern MotionState080FE2E8 *func_08005BFC(void *);
extern void func_080DBD78(void *, s16 *, s16 *, s16 *);
extern void *func_080DFA30(void *, u16, u8, u8, u8, u16, void *);
extern void func_080DE10C(void *, u16);
extern void func_08005BA8(void *, u16);
extern void func_080D5C20(void *);
extern void func_0801115C(void *, u8);
extern void func_080FDEE8(void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080E051C(void *);
extern int func_080D8858(void *, int);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_080FE2E8(void *task, Descriptor080FE2E8 *descriptor,
                  Payload080FE2E8 *payload)
{
    MotionDescriptor080FE2E8 motion;

    switch (descriptor->phase) {
    case 0: {
        void *actor;
        int delay;

        payload->mode = descriptor->mode;
        actor = descriptor->actor;
        payload->actor = actor;
        delay = 4;
        if (payload->mode)
            delay = 0;
        payload->initial_task = func_080E03F8(actor, &data_0839D844, delay,
                                              0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 direction;

        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD47C(payload->actor);
        payload->sprite_task = func_080DE4B0(payload->object,
            &payload->finished, 0, 2, 0, 0, 0, task);
        func_080DBD5C(payload->object, &payload->from_x, &payload->from_y,
                      &payload->from_z);
        if (func_080DD494(payload->actor)) {
            payload->target = func_080DD4B4(payload->actor, 0);
            func_080DBD5C(payload->target, &payload->to_x, &payload->to_y,
                          &payload->to_z);
        } else {
            func_080D8B7C(payload->actor, &payload->to_x, &payload->to_y,
                          &payload->to_z);
        }
        direction = func_080DBC88(payload->object);
        motion.palette = func_080DD488(payload->actor);
        motion.direction = (s8)direction;
        motion.from = &payload->from_x;
        motion.to = &payload->to_x;
        payload->motion_task = func_08005B6C(func_080FDF90, 0x218, &motion,
                                             task);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        Target080FE2E8 *target;

        if (func_08005BAC(payload->motion_task) != 0x103)
            break;
        target = func_080DD4A4(payload->actor, 0);
        if (target->kind == 6)
            payload->alternate = 1;
        if (payload->alternate) {
            u16 duration = func_08005BFC(payload->motion_task)->duration + 18;
            s16 x, y, z;

            func_080DBD78(payload->object, &x, &y, &z);
            payload->effect_task = func_080DFA30(target, 0x3D1, 6, x,
                                                 z, duration, task);
        }
        func_080DE10C(payload->object, 0x98);
        descriptor->phase++;
        break;
    }
    case 0x102: {
        MotionState080FE2E8 *state;

        if (!payload->finished)
            break;
        func_08005BA8(payload->motion_task, 0x104);
        state = func_08005BFC(payload->motion_task);
        func_080D5C20(state->motion);
        func_0801115C(state->sprite, 1);
        func_080FDEE8(payload->actor, payload->target);
        payload->sound_task = func_080DFD8C(&data_0839D8B8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x103: {
        ChildDescriptor080FE2E8 child;

        payload->motion_task = func_080E051C(payload->motion_task);
        if (payload->motion_task)
            break;
        child.actor = func_080DD4A4(payload->actor, 0);
        if (payload->target) {
            if (!payload->alternate)
                payload->child_task = func_08005B6C(func_080FE234, 0x24,
                                                    &child, task);
        } else {
            func_080D8858(payload->actor, 0);
        }
        descriptor->phase++;
        break;
    }
    case 0x104:
        if (!func_080DE1F0(payload->object))
            break;
        payload->child_task = func_080E051C(payload->child_task);
        if (payload->child_task)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
