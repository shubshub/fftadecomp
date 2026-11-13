#include "ffta.h"

// Complete [0x0809A664, 0x0809A68C): 40 bytes.
// 00b582b00906090e054a00910192006904496a462df022fb02b001bc004700001dad0908e9ab0908
typedef struct ListNode0809A664 ListNode0809A664;
typedef struct ListContext0809A664 ListContext0809A664;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A664 *objects;
} State0809A664;

typedef u32 (*ValueCallback0809A664)(void *object, u8 value);

typedef struct {
    u32 value;
    ValueCallback0809A664 callback;
} Closure0809A664;

extern void func_080C7CC0(ListContext0809A664 *context,
                          u32 (*callback)(ListNode0809A664 *, void *),
                          Closure0809A664 *closure);
extern u32 func_0809ABE8(ListNode0809A664 *node, void *closure);
extern u32 func_0809AD1C(void *object, u8 value);

void func_0809A664(State0809A664 *state, u8 value)
{
    Closure0809A664 closure;
    ValueCallback0809A664 callback = func_0809AD1C;

    closure.value = value;
    closure.callback = callback;
    func_080C7CC0(state->objects, func_0809ABE8, &closure);
}
