#include "ffta.h"

struct Actor080C2618 {
    u8 unknown00[0xF8];
    u8 state;
};

struct Unit080C2618 {
    struct Actor080C2618 *actor;
};

struct Result080C2618 {
    u16 action;
    u16 parameter;
    s32 value;
    u8 unknown08[2];
    u16 success;
    s16 value0C;
    s16 value0E;
    u8 value10;
    u8 flags;
};

extern u8 func_080C2314(struct Actor080C2618 *source,
                       struct Actor080C2618 *target, u16 action, u16 parameter,
                       s32 *value, s16 *value0C, s16 *value0E, u8 *flags,
                       u16 argument8);
extern u8 func_0813413C(struct Actor080C2618 *actor, u16 action);
extern void *func_08096D7C(void);
extern struct Unit080C2618 *func_08099544(void *context);
extern u8 func_0812E4A8(const void *actor);
extern u8 func_080CD944(const void *actor);
extern u8 func_080C82B8(const void *actor);
extern u8 func_0813569C(struct Actor080C2618 *source,
                       struct Actor080C2618 *target, u16 action, u32 mode);

/* Complete [0x080C2618, 0x080C26EC): 212 bytes, 98 instructions. */
void func_080C2618(struct Result080C2618 *result,
                   struct Unit080C2618 *source, struct Unit080C2618 *target,
                   u16 action, u16 parameter, u16 argument5)
{
    u8 previous;

    result->action = action;
    result->parameter = parameter;
    previous = source->actor->state;
    source->actor->state = target->actor->state;
    result->success = func_080C2314(source->actor, target->actor, action, parameter,
                                    &result->value, &result->value0C,
                                    &result->value0E, &result->flags, argument5);
    source->actor->state = previous;

    if (result->success) {
        struct Unit080C2618 *current;

        result->value10 = func_0813413C(source->actor, action);
        current = func_08099544(func_08096D7C());
        if (current && func_0812E4A8(current->actor) &&
            !func_080CD944(source->actor) && !func_080C82B8(source->actor) &&
            func_0813569C(source->actor, target->actor, action, 0))
            result->flags |= 2;
    }
}
