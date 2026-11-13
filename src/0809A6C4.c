#include "ffta.h"

// Complete [0x0809A6C4, 0x0809A6EC): 40 bytes.
// 00b582b00906090e054a00910192006904496a462df0f2fa02b001bc00470000e5ac0908e9ab0908
typedef struct ListNode0809A6C4 ListNode0809A6C4;
typedef struct ListContext0809A6C4 ListContext0809A6C4;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A6C4 *objects;
} State0809A6C4;

typedef u32 (*ValueCallback0809A6C4)(void *value, u8 argument);

typedef struct {
    u32 argument;
    ValueCallback0809A6C4 callback;
} Closure0809A6C4;

extern void func_080C7CC0(ListContext0809A6C4 *context,
                          u32 (*callback)(ListNode0809A6C4 *, void *),
                          Closure0809A6C4 *closure);
extern u32 func_0809ABE8(ListNode0809A6C4 *node, void *closure);
extern u32 func_0809ACE4(void *value, u8 argument);

void func_0809A6C4(State0809A6C4 *state, u8 value)
{
    Closure0809A6C4 closure;
    ValueCallback0809A6C4 callback = func_0809ACE4;

    closure.argument = value;
    closure.callback = callback;
    func_080C7CC0(state->objects, func_0809ABE8, &closure);
}
