#include "ffta.h"

/* Complete target [0x08099D60,0x08099D8C): 44 bytes. */
typedef struct ListNode08099D60 ListNode08099D60;
typedef struct ListContext08099D60 ListContext08099D60;

typedef struct {
    u32 count;
    void **cursor;
} State08099D60;

typedef u32 (*ValueCallback08099D60)(void *value, State08099D60 *argument);

typedef struct {
    State08099D60 *argument;
    ValueCallback08099D60 callback;
} Closure08099D60;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099D60 *list;
} Owner08099D60;

extern u32 func_0809AC00(ListNode08099D60 *node, Closure08099D60 *closure);
extern u32 func_0809AC20(void *value, State08099D60 *state);
extern void func_080C7D18(ListContext08099D60 *list,
                          u32 (*callback)(ListNode08099D60 *, Closure08099D60 *),
                          Closure08099D60 *closure);

u32 func_08099D60(Owner08099D60 *owner, void **out)
{
    State08099D60 state;
    Closure08099D60 closure;
    ValueCallback08099D60 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D18(owner->list, func_0809AC00, &closure);
    return state.count;
}
