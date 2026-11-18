#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

typedef struct {
    u8 unknown_00[0x30];
    u32 flags;
} UnitObject;

extern u8 func_080CD8FC(const void *unit);
extern void func_080CDD88(void *unit, u8 enabled);
extern void func_08131DD4(void *state, s32 index);
extern void func_080CDDD0(Unit *unit, u8 value);
extern void * func_08096D7C(void);
extern UnitObject * func_08099560(void *owner, u32 key);
extern void func_080CE314(Unit *unit, u8 enabled);

void func_08132938(ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        if (!(state->flags & 0x10)) {
            func_080CDD88(state->target, 0);
            state->flags |= 0x100;
        }
    } else {
        func_08131DD4(state, 6);
        if (!(state->flags & 0x10)) {
            UnitObject *object;

            func_080CDDD0(state->target, 1);
            object = func_08099560(func_08096D7C(), (u32)state->target);
            if (object) {
                if (object->flags & 8)
                    func_080CE314(state->target, 1);
                else
                    func_080CE314(state->target, 0);
            }
        }
    }
}
