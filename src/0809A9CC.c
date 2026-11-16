#include "ffta.h"

/* Complete [0x0809A9CC, 0x0809A9F0): 36 bytes.
 * 00b582b0054a002100910192006904496a462df06ff902b001bc0047ddad0908e9ab0908 */
typedef struct ListNode0809A9CC ListNode0809A9CC;
typedef struct ListContext0809A9CC ListContext0809A9CC;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A9CC *objects;
} State0809A9CC;

typedef u32 (*ValueCallback0809A9CC)(void *value, void *argument);

typedef struct {
    void *argument;
    ValueCallback0809A9CC callback;
} Closure0809A9CC;

extern void func_080C7CC0(ListContext0809A9CC *context,
                          u32 (*callback)(ListNode0809A9CC *, void *),
                          Closure0809A9CC *closure);
extern u32 func_0809ABE8(ListNode0809A9CC *node, void *closure);
extern u32 func_0809ADDC(void *value, void *argument);

void func_0809A9CC(State0809A9CC *state)
{
    Closure0809A9CC closure;
    ValueCallback0809A9CC callback = func_0809ADDC;

    closure.argument = 0;
    closure.callback = callback;
    func_080C7CC0(state->objects, func_0809ABE8, &closure);
}
