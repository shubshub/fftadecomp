#include "ffta.h"

// Complete target [0x0809A204,0x0809A244): 64 bytes.
typedef struct ListNode0809A204 ListNode0809A204;
typedef struct ListContext0809A204 ListContext0809A204;
typedef struct FlagState0809A204 FlagState0809A204;

typedef u32 (*ValueCallback0809A204)(FlagState0809A204 *value, u32 *result);

typedef struct {
    u32 *argument;
    ValueCallback0809A204 callback;
} Closure0809A204;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A204 *list;
    u8 unknown_14[0x10];
    u32 flags;
} Owner0809A204;

extern u32 func_0809ABE8(ListNode0809A204 *node, Closure0809A204 *closure);
extern u32 func_0809AC88(FlagState0809A204 *state, u32 *result);
extern void func_080C7CC0(ListContext0809A204 *list,
                          u32 (*callback)(ListNode0809A204 *, Closure0809A204 *),
                          Closure0809A204 *closure);

u8 func_0809A204(Owner0809A204 *owner)
{
    u32 found;
    Closure0809A204 closure;
    ValueCallback0809A204 callback;

    if (!(owner->flags & 1))
        return 1;
    found = 0;
    callback = func_0809AC88;
    closure.argument = &found;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
    return found;
}
