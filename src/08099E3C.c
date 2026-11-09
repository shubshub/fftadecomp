#include "ffta.h"

/* Complete target [0x08099E3C,0x08099E68): 44 bytes. */
typedef struct ListNode08099E3C ListNode08099E3C;
typedef struct ListContext08099E3C ListContext08099E3C;

typedef struct {
    u32 count;
    void **cursor;
} State08099E3C;

typedef u32 (*ValueCallback08099E3C)(void *value, State08099E3C *argument);

typedef struct {
    State08099E3C *argument;
    ValueCallback08099E3C callback;
} Closure08099E3C;

typedef struct {
    u8 unknown_00[0x18];
    ListContext08099E3C *list;
} Owner08099E3C;

extern u32 func_0809AC00(ListNode08099E3C *node, Closure08099E3C *closure);
extern u32 func_0809AC20(void *value, State08099E3C *state);
extern void func_080C7D70(ListContext08099E3C *list,
                          u32 (*callback)(ListNode08099E3C *, Closure08099E3C *),
                          Closure08099E3C *closure);

u32 func_08099E3C(Owner08099E3C *owner, void **out)
{
    State08099E3C state;
    Closure08099E3C closure;
    ValueCallback08099E3C callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D70(owner->list, func_0809AC00, &closure);
    return state.count;
}
