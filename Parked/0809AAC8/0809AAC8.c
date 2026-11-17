#include "ffta.h"

typedef struct ListNode0809AAC8 ListNode0809AAC8;
typedef struct ListContext0809AAC8 ListContext0809AAC8;

typedef struct {
    u8 unknown_00[4];
    u32 unknown_04;
} Object0809AAC8;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809AAC8 *objects;
} State0809AAC8;

typedef struct {
    u32 count;
    Object0809AAC8 **cursor;
} Output0809AAC8;

typedef u32 (*ValueCallback0809AAC8)(void *value, Output0809AAC8 *output);

typedef struct {
    Output0809AAC8 *argument;
    ValueCallback0809AAC8 callback;
} Closure0809AAC8;

extern void func_080C7CC0(ListContext0809AAC8 *context,
                          u32 (*callback)(ListNode0809AAC8 *, void *),
                          Closure0809AAC8 *closure);
extern u32 func_0809ABE8(ListNode0809AAC8 *node, void *closure);
extern u32 func_0809AC20(void *value, Output0809AAC8 *output);

static inline void Clear0809AAC8(Object0809AAC8 **cursor, int count)
{
    int i;

    for (i = 0; i < count; i++)
        cursor[i]->unknown_04 = 0;
}

// Target: complete [0x0809AAC8, 0x0809AB0C), 68 bytes, 34 instructions.
void func_0809AAC8(State0809AAC8 *state)
{
    Object0809AAC8 *objects[13];
    Output0809AAC8 output;
    Closure0809AAC8 closure;
    ValueCallback0809AAC8 callback;

    output.count = 0;
    output.cursor = objects;
    callback = func_0809AC20;
    closure.argument = &output;
    closure.callback = callback;
    func_080C7CC0(state->objects, func_0809ABE8, &closure);
    Clear0809AAC8(objects, output.count);
}
