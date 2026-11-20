#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u8 unknown_1A[0xF6 - 0x1A];
    u8 x;
    u8 y;
    u8 direction;
} Object;

struct ActionState {
    Object *source;
    u8 unknown_04[4];
    Object *target;
    u8 unknown_0C[0x1A];
    u16 flags;
};

struct Effect {
    void (*apply)(struct ActionState *state);
    u8 unknown_04[8];
};

extern const struct Effect data_083A87B0[];
extern u32 func_08002804(void);
extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern s32 func_0812D7FC(const Object *source, const Object *target, u8 average, s16 *kind);

/* 0x0813233C..0x081323D0, 148 bytes. Effect descriptor slot 29. */
void func_0813233C(struct ActionState *state)
{
    s16 kind;
    s16 threshold;
    s16 roll;

    if (func_080CD8FC(state->target)) {
        func_080CDD88(state->target, 0);
        state->flags |= 0x100;
    } else {
        threshold = (s16)func_0812D7FC(state->source, state->target, 0, &kind) * 10;
        roll = (s16)func_08002804() % 1001;
        if (threshold >= roll) {
            if (kind <= 0)
                state->target->field_18 = 1;
            else
                data_083A87B0[kind].apply(state);
        } else {
            state->flags |= 0x100;
        }
    }
}
