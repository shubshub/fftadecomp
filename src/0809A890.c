#include "ffta.h"

// Complete target [0x0809A890, 0x0809A8C8): 56 bytes, 23 instructions.
typedef struct ListNode ListNode;
typedef struct ListContext ListContext;
typedef struct EntityHolder EntityHolder;

typedef struct {
    u8 step;
    u8 flags;
    u8 unknown_02[2];
} StepState; /* 4 bytes: func_0809A77C clears sizeof(StepState) == 4 */

typedef struct {
    StepState *argument;
    s32 (*callback)(EntityHolder *holder, StepState *state);
} VisitorContext;

typedef struct {
    u8 unknown_00[0x14];
    ListContext *list;
} Owner;

extern s32 func_0809AD48(EntityHolder *holder, StepState *state);
extern u32 func_0809ABE8(ListNode *node, void *payload);
extern void func_080C7CC0(ListContext *list,
                         u32 (*callback)(ListNode *, void *), void *payload);

u32 func_0809A890(Owner *owner)
{
    StepState state;
    /* through a pointer: a direct state.step store on this word-sized
       struct compiles to a word read-modify-write, not the ROM's strb */
    StepState *step_state = &state;
    VisitorContext visitor;

    step_state->step = 0;
    {
        s32 (*callback)(EntityHolder *, StepState *) = func_0809AD48;

        visitor.argument = step_state;
        visitor.callback = callback;
        func_080C7CC0(owner->list, func_0809ABE8, &visitor);
    }
    if (step_state->step != 0)
        return 1;
    return 0;
}
