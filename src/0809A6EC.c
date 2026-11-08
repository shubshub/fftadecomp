#include "ffta.h"

/* Target: complete [0x0809A6EC, 0x0809A710), 36 bytes. */
typedef struct ListNode0809A6EC ListNode0809A6EC;
typedef struct ListContext0809A6EC ListContext0809A6EC;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A6EC *objects;
} State0809A6EC;

typedef u32 (*ValueCallback0809A6EC)(void *value, void *argument);

typedef struct {
    void *argument;
    ValueCallback0809A6EC callback;
} Closure0809A6EC;

extern void func_080C7CC0(ListContext0809A6EC *context,
                          u32 (*callback)(ListNode0809A6EC *, void *),
                          Closure0809A6EC *closure);
extern u32 func_0809ABE8(ListNode0809A6EC *node, void *closure);
extern u32 func_0809ACB4(void *object, void *argument);

void func_0809A6EC(State0809A6EC *state)
{
    Closure0809A6EC closure;
    ValueCallback0809A6EC callback = func_0809ACB4;

    closure.argument = 0;
    closure.callback = callback;
    func_080C7CC0(state->objects, func_0809ABE8, &closure);
}
