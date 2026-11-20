#include "ffta.h"

/* Complete [0x0813325C, 0x081332F8), 156 bytes. */
typedef struct {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x0C];
    u16 removed_item;
    u8 unknown_1A[0x0C];
    u16 flags;
} ActionState;

extern u32 func_0812F0CC(const void *unit, u16 *output);
extern u32 func_08002804(void);
extern s32 func_080C7EA4(const void *unit, u32 field);
extern void func_080CAF78(void *unit, u16 item, u8 slot);
extern u8 func_080CB54C(void *unit, u8 enabled);
extern u8 func_08131BB8(void *unit);
extern s32 func_080CA9E8(u16 item, u8 quantity);
extern void func_080CA2E8(void *unit);

void func_0813325C(ActionState *state)
{
    u16 items[2];
    s32 count;
    s32 index;
    s32 slot;

    if (state->flags & 0x10)
        return;
    count = func_0812F0CC(state->target, items);
    if (count == 0)
        return;
    index = (s16)func_08002804() % count;
    for (slot = 0; slot < 5; slot++) {
        u16 item = func_080C7EA4(state->target, (u8)(slot + 0x1D));

        if (item && item == items[index]) {
            func_080CAF78(state->target, 0, slot);
            func_080CB54C(state->target, 1);
            if (func_08131BB8(state->target))
                func_080CA9E8(item, 1);
            state->removed_item = item;
            break;
        }
    }
    func_080CA2E8(state->target);
}
