#include "ffta.h"

typedef struct ListNode ListNode;
typedef struct ListContext ListContext;
typedef struct EntityHolder EntityHolder;

typedef struct {
    u8 step;
    u8 flags;
    u8 unknown_02[2];
} StepState;

typedef struct {
    StepState *argument;
    u8 (*callback)(EntityHolder *value, StepState *argument);
} VisitorContext;

typedef struct {
    u8 unknown_00[20];
    ListContext *list;
} Owner;

extern void (*const g_callbacks_0836D4B8[])(void *destination, u32 size);
extern u8 func_08098BB0(EntityHolder *value, StepState *argument);
extern u32 func_0809ABE8(ListNode *node, void *payload);
extern void func_080C7CC0(ListContext *list,
                         u32 (*callback)(ListNode *, void *), void *payload);

/* Complete target [0x0809A740, 0x0809A77C): 60 bytes. */
u8 func_0809A740(Owner *owner)
{
    VisitorContext visitor;
    StepState state;

    g_callbacks_0836D4B8[0](&state, sizeof(state));
    {
        u8 (*callback)(EntityHolder *, StepState *) = func_08098BB0;

        visitor.argument = &state;
        visitor.callback = callback;
        func_080C7CC0(owner->list, func_0809ABE8, &visitor);
    }
    return state.step;
}
