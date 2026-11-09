#include "ffta.h"

/* Complete target [0x08099DB8,0x08099DE4): 44 bytes. */
typedef struct ListNode08099DB8 ListNode08099DB8;
typedef struct ListContext08099DB8 ListContext08099DB8;

typedef struct {
    u32 count;
    void **cursor;
} State08099DB8;

typedef u32 (*ValueCallback08099DB8)(void *value, State08099DB8 *argument);

typedef struct {
    State08099DB8 *argument;
    ValueCallback08099DB8 callback;
} Closure08099DB8;

typedef struct {
    u8 unknown_00[0x14];
    ListContext08099DB8 *list;
} Owner08099DB8;

extern u32 func_0809AC00(ListNode08099DB8 *node, Closure08099DB8 *closure);
extern u32 func_0809AC20(void *value, State08099DB8 *state);
extern void func_080C7D18(ListContext08099DB8 *list,
                          u32 (*callback)(ListNode08099DB8 *, Closure08099DB8 *),
                          Closure08099DB8 *closure);

u32 func_08099DB8(Owner08099DB8 *owner, void **out)
{
    State08099DB8 state;
    Closure08099DB8 closure;
    ValueCallback08099DB8 callback;

    state.count = 0;
    state.cursor = out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7D18(owner->list, func_0809AC00, &closure);
    return state.count;
}
