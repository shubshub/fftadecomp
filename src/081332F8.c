#include "ffta.h"

/* Target: complete [0x081332F8, 0x08133386), 142 bytes. */
typedef struct {
    u8 unknown_00[8];
    void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} ActionState;

extern u32 func_0812F0CC(const void *unit, u16 *entries);
extern s32 func_080C7EA4(const void *unit, u32 field);
extern void func_080CAF78(void *unit, u16 entry, u8 slot);
extern u8 func_080CB54C(void *unit, u8 enabled);
extern void func_080CA2E8(void *unit);

void func_081332F8(ActionState *state)
{
    u16 entries[2];
    s32 count;
    s32 slot;

    if (state->flags & 0x10)
        return;
    count = func_0812F0CC(state->target, entries);
    if (count <= 0)
        return;

    for (slot = 0; slot < 5; slot++) {
        u16 entry = func_080C7EA4(state->target, (u8)(slot + 0x1D));
        s32 i;

        if (entry != 0) {
            for (i = 0; i < count; i++) {
                if (entries[i] == entry) {
                    func_080CAF78(state->target, 0, slot);
                    func_080CB54C(state->target, 1);
                }
            }
        }
    }
    func_080CA2E8(state->target);
}
