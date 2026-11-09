#include "ffta.h"

/* Complete target [0x08099D8C,0x08099DB8): 44 bytes. */
typedef struct ListNode08099D8C ListNode08099D8C;
typedef struct ListContext08099D8C ListContext08099D8C;

typedef struct {
    u32 count;
    void **cursor;
} State08099D8C;

typedef u32 (*ValueCallback08099D8C)(void *value, State08099D8C *argument);

typedef struct {
    State08099D8C *argument;
    ValueCallback08099D8C callback;
} Closure08099D8C;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099D8C *list;
} Owner08099D8C;

extern u32 func_0809AC00(ListNode08099D8C *node, Closure08099D8C *closure);
extern u32 func_0809AC20(void *value, State08099D8C *state);
extern void func_080C7D70(ListContext08099D8C *list,
                          u32 (*callback)(ListNode08099D8C *, Closure08099D8C *),
                          Closure08099D8C *closure);

u32 func_08099D8C(Owner08099D8C *owner, void **out)
{
    State08099D8C state;
    Closure08099D8C closure;
    ValueCallback08099D8C callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D70(owner->list, func_0809AC00, &closure);
    return state.count;
}
