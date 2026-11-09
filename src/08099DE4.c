#include "ffta.h"

/* Complete target [0x08099DE4,0x08099E10): 44 bytes. */
typedef struct ListNode08099DE4 ListNode08099DE4;
typedef struct ListContext08099DE4 ListContext08099DE4;

typedef struct {
    u32 count;
    void **cursor;
} State08099DE4;

typedef u32 (*ValueCallback08099DE4)(void *value, State08099DE4 *argument);

typedef struct {
    State08099DE4 *argument;
    ValueCallback08099DE4 callback;
} Closure08099DE4;

typedef struct {
    u8 unknown_00[0x14];
    ListContext08099DE4 *list;
} Owner08099DE4;

extern u32 func_0809AC00(ListNode08099DE4 *node, Closure08099DE4 *closure);
extern u32 func_0809AC20(void *value, State08099DE4 *state);
extern void func_080C7D70(ListContext08099DE4 *list,
                          u32 (*callback)(ListNode08099DE4 *, Closure08099DE4 *),
                          Closure08099DE4 *closure);

u32 func_08099DE4(Owner08099DE4 *owner, void **out)
{
    State08099DE4 state;
    Closure08099DE4 closure;
    ValueCallback08099DE4 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D70(owner->list, func_0809AC00, &closure);
    return state.count;
}
