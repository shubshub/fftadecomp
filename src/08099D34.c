#include "ffta.h"

/* Complete target [0x08099D34,0x08099D60): 44 bytes. */
typedef struct ListNode08099D34 ListNode08099D34;
typedef struct ListContext08099D34 ListContext08099D34;

typedef struct {
    u32 count;
    void **cursor;
} State08099D34;

typedef u32 (*ValueCallback08099D34)(void *value, State08099D34 *argument);

typedef struct {
    State08099D34 *argument;
    ValueCallback08099D34 callback;
} Closure08099D34;

typedef struct {
    u8 unknown_00[0x18];
    ListContext08099D34 *list;
} Owner08099D34;

extern u32 func_0809ABE8(ListNode08099D34 *node, Closure08099D34 *closure);
extern u32 func_0809AC20(void *value, State08099D34 *state);
extern void func_080C7CC0(ListContext08099D34 *list,
                          u32 (*callback)(ListNode08099D34 *, Closure08099D34 *),
                          Closure08099D34 *closure);

u32 func_08099D34(Owner08099D34 *owner, void **out)
{
    State08099D34 state;
    Closure08099D34 closure;
    ValueCallback08099D34 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
    return state.count;
}
