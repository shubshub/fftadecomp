#include "ffta.h"

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    struct Actor *actor;
};

struct Actor {
    void *object;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 counter;
    u16 delay;
    u32 unknown_04;
    struct Actor *actor;
    void *object;
    void *pieces[28];
    struct InterpolationState actor_y;
    struct InterpolationState x_motion[28];
    struct InterpolationState y_motion[28];
    void *child;
};

struct TimedDefinition {
    u8 time;
    u8 kind;
    s16 x;
    s16 y;
    u16 unknown_06;
};

extern const u8 data_083A33C4[];
extern const u8 data_08504D8C[];
extern const struct TimedDefinition data_083A33F8[];
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080E064C(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011428(void *);
extern void *func_08011484(void *);
extern u8 func_080D5F24(void **, u8);

/* Complete target: [0x08111A5C, 0x08111C7C), 544 bytes. */
u32 func_08111A5C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u8 index;

    switch (descriptor->phase) {
    case 0:
        payload->actor = descriptor->actor;
        func_080E0608(&payload->actor_y, 64, 64, 20);
        payload->counter = 30;
        break;
    case 1:
        break;
    case 0x100:
        if (!func_080E0690(&payload->actor_y)) {
            func_080E064C(&payload->actor_y);
            func_080107D4(payload->actor->object, 120, payload->actor_y.current, 0);
        } else if (--payload->counter == 0) {
            payload->child = func_080DFD8C(data_083A33C4, 1, 4, 0, task);
            payload->delay = 30;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (payload->delay != 0) {
            if (--payload->delay == 0)
                payload->object = func_080D5CC0(data_08504D8C, 2, 120, 124,
                                               0x30B, 8, 0, 0);
        }
        for (index = 0; index < 28; index++) {
            if (payload->pieces[index] != 0) {
                if (func_080E0690(&payload->x_motion[index])) {
                    func_08011428(payload->pieces[index]);
                    payload->pieces[index] = 0;
                } else {
                    func_080E064C(&payload->x_motion[index]);
                    func_080E064C(&payload->y_motion[index]);
                    func_080107D4(payload->pieces[index],
                        payload->x_motion[index].current,
                        payload->y_motion[index].current, 0);
                }
            }
        }
        for (index = 0; index < 28; index++) {
            const struct TimedDefinition *definition = &data_083A33F8[index];

            if (payload->counter == definition->time) {
                payload->pieces[index] = func_080D5CC0(data_08504D8C,
                    definition->kind, definition->x, definition->y,
                    0x30B, 8, 0, 0);
                func_080E0608(&payload->x_motion[index], definition->x, 120, 24);
                func_080E0608(&payload->y_motion[index], definition->y, 124, 24);
            }
        }
        payload->counter++;
        payload->object = func_08011484(payload->object);
        if (payload->object == 0 &&
            payload->counter >= data_083A33F8[27].time + 24 &&
            func_080D5F24(payload->pieces, 28))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
