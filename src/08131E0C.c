#include "ffta.h"

/* Action descriptor slot 2, 0x08131E0C..0x08131E2E.
 * 10b5041c0121fff7dfffe18c10200840002803d1a06801219bf77aff10bc01bc0047
 */
typedef struct {
    u8 unknown_00[0xE8];
    u8 flags;
} State;

struct ActionState {
    u8 unknown00[8];
    State *target;
    u8 unknown0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CDD1C(State *state, u8 enabled);

void func_08131E0C(struct ActionState *state)
{
    func_08131DD4((u8 *)state, 1);
    if (!(state->flags & 0x10))
        func_080CDD1C(state->target, 1);
}
