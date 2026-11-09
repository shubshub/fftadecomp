#include "ffta.h"

/* Complete target [0x08099E10,0x08099E3C): 44 bytes. */
typedef struct ListNode08099E10 ListNode08099E10;
typedef struct ListContext08099E10 ListContext08099E10;

typedef struct {
    u32 count;
    void **cursor;
} State08099E10;

typedef u32 (*ValueCallback08099E10)(void *value, State08099E10 *argument);

typedef struct {
    State08099E10 *argument;
    ValueCallback08099E10 callback;
} Closure08099E10;

typedef struct {
    u8 unknown_00[0x18];
    ListContext08099E10 *list;
} Owner08099E10;

extern u32 func_0809AC00(ListNode08099E10 *node, Closure08099E10 *closure);
extern u32 func_0809AC20(void *value, State08099E10 *state);
extern void func_080C7D18(ListContext08099E10 *list,
                          u32 (*callback)(ListNode08099E10 *, Closure08099E10 *),
                          Closure08099E10 *closure);

u32 func_08099E10(Owner08099E10 *owner, void **out)
{
    State08099E10 state;
    Closure08099E10 closure;
    ValueCallback08099E10 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D18(owner->list, func_0809AC00, &closure);
    return state.count;
}
