#include "ffta.h"

/* Complete target [0x08099CDC,0x08099D08): 44 bytes. */
typedef struct ListNode08099CDC ListNode08099CDC;
typedef struct ListContext08099CDC ListContext08099CDC;

typedef struct {
    u32 count;
    void **cursor;
} State08099CDC;

typedef u32 (*ValueCallback08099CDC)(void *value, State08099CDC *argument);

typedef struct {
    State08099CDC *argument;
    ValueCallback08099CDC callback;
} Closure08099CDC;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099CDC *list;
} Owner08099CDC;

extern u32 func_0809ABE8(ListNode08099CDC *node, Closure08099CDC *closure);
extern u32 func_0809AC20(void *value, State08099CDC *state);
extern void func_080C7CC0(ListContext08099CDC *list,
                          u32 (*callback)(ListNode08099CDC *, Closure08099CDC *),
                          Closure08099CDC *closure);

u32 func_08099CDC(Owner08099CDC *owner, void **out)
{
    State08099CDC state;
    Closure08099CDC closure;
    ValueCallback08099CDC callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
    return state.count;
}
