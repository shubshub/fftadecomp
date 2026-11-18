#include "ffta.h"

/* Action descriptor slot 3, 0x08131E30..0x08131E82.
 * 10b5041c2321fff7cdff201c2521fff7c9ff201c2721fff7c5ff201c2921fff7c1ffe18c1020084000280fd1a06801219cf7b8f9a06801219cf7d8f9a06801219cf7f8f9a06801219cf716fa10bc01bc0047
 */
struct ActionState {
    u8 unknown00[8];
    void *target;
    u8 unknown0C[0x1A];
    u16 flags;
};

extern void func_08131DD4(u8 *buffer, s32 index);
extern void func_080CE1D4(void *object, u8 enabled);
extern void func_080CE21C(void *object, u8 enabled);
extern void func_080CE264(void *object, u8 enabled);
extern void func_080CE2A8(void *object, u8 enabled);

void func_08131E30(struct ActionState *state)
{
    func_08131DD4((u8 *)state, 0x23);
    func_08131DD4((u8 *)state, 0x25);
    func_08131DD4((u8 *)state, 0x27);
    func_08131DD4((u8 *)state, 0x29);

    if (!(state->flags & 0x10)) {
        func_080CE1D4(state->target, 1);
        func_080CE21C(state->target, 1);
        func_080CE264(state->target, 1);
        func_080CE2A8(state->target, 1);
    }
}
