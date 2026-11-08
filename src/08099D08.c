#include "ffta.h"

/* Complete target [0x08099D08,0x08099D34): 44 bytes. */
typedef struct ListNode08099D08 ListNode08099D08;
typedef struct ListContext08099D08 ListContext08099D08;

typedef struct {
    u32 count;
    void **cursor;
} State08099D08;

typedef u32 (*ValueCallback08099D08)(void *value, State08099D08 *argument);

typedef struct {
    State08099D08 *argument;
    ValueCallback08099D08 callback;
} Closure08099D08;

typedef struct {
    u8 unknown_00[0x14];
    ListContext08099D08 *list;
} Owner08099D08;

extern u32 func_0809ABE8(ListNode08099D08 *node, Closure08099D08 *closure);
extern u32 func_0809AC20(void *value, State08099D08 *state);
extern void func_080C7CC0(ListContext08099D08 *list,
                          u32 (*callback)(ListNode08099D08 *, Closure08099D08 *),
                          Closure08099D08 *closure);

u32 func_08099D08(Owner08099D08 *owner, void **out)
{
    State08099D08 state;
    Closure08099D08 closure;
    ValueCallback08099D08 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
    return state.count;
}
