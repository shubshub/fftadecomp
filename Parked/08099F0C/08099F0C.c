#include "ffta.h"

// Complete target [0x08099F0C,0x08099F58): 76 bytes.
typedef struct ListNode08099F0C ListNode08099F0C;
typedef struct ListContext08099F0C ListContext08099F0C;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099F0C *list;
} Lookup08099F0C;

typedef struct {
    u8 unknown_00[0x80];
    Lookup08099F0C *lookup;
} Object08099F0C;

typedef struct {
    Object08099F0C *owner;
    u32 x : 8;
    u32 z : 8;
} State08099F0C;

typedef s32 (*ValueCallback08099F0C)(void *value, State08099F0C *argument);

typedef struct {
    State08099F0C *argument;
    ValueCallback08099F0C callback;
} Closure08099F0C;

extern s32 func_0809ABE8(ListNode08099F0C *node, Closure08099F0C *closure);
extern s32 func_0809AC30(void *value, State08099F0C *state);
extern void func_080C7CC0(ListContext08099F0C *list,
                          s32 (*callback)(ListNode08099F0C *, Closure08099F0C *),
                          Closure08099F0C *closure);

void func_08099F0C(Object08099F0C *object, u8 x, u8 z)
{
    State08099F0C state;
    Closure08099F0C closure;
    ValueCallback08099F0C callback;
    Lookup08099F0C *lookup;

    state.owner = object;
    state.x = x;
    state.z = z;
    lookup = object->lookup;
    callback = func_0809AC30;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(lookup->list, func_0809ABE8, &closure);
}
