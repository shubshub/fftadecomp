#include "ffta.h"

/* Action descriptor slot 19, 0x081320E8..0x08132136.
 * 10b5041ca0689bf705fc000600280ad0a06800219bf744fee18c80225200101c0843e08410e0201c1721fff75ffee18c10200840002807d1a06801219bf794ffa06802219cf784f910bc01bc0047
 */
struct State;

struct ActionState {
    u8 unknown00[8];
    struct State *target;
    u8 unknown0C[0x1A];
    u16 flags;
};

extern u8 func_080CD8FC(const void *object);
extern void func_080CDD88(void *object, u8 enabled);
extern void func_080CE050(void *object, u8 enabled);
extern void func_080CE438(struct State *state, u8 value);
extern void func_08131DD4(u8 *buffer, s32 index);

void func_081320E8(struct ActionState *state)
{
    if (func_080CD8FC(state->target)) {
        func_080CDD88(state->target, 0);
        state->flags |= 0x100;
    } else {
        func_08131DD4((u8 *)state, 0x17);
        if (!(state->flags & 0x10)) {
            func_080CE050(state->target, 1);
            func_080CE438(state->target, 2);
        }
    }
}
