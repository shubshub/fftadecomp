#include "ffta.h"

// Complete target [0x0809A070,0x0809A09C): 44 bytes.
// 10b582b0041c0749a0690090019106496a462df01dfea0692df0defd02b010bc01bc00476dac0908e9ab0908
typedef struct ListNode0809A070 ListNode0809A070;
typedef struct Collection0809A070 Collection0809A070;

typedef s32 (*ValueCallback0809A070)(void *value, Collection0809A070 *collection);

typedef struct {
    Collection0809A070 *argument;
    ValueCallback0809A070 callback;
} Closure0809A070;

typedef struct {
    u8 unknown_00[0x18];
    Collection0809A070 *collection;
} Owner0809A070;

extern u32 func_0809ABE8(ListNode0809A070 *node, Closure0809A070 *closure);
extern s32 func_0809AC6C(void *object, Collection0809A070 *collection);
extern void func_080C7CC0(Collection0809A070 *list,
                          u32 (*callback)(ListNode0809A070 *, Closure0809A070 *),
                          Closure0809A070 *closure);
extern void func_080C7C48(Collection0809A070 *list);

void func_0809A070(Owner0809A070 *owner)
{
    Closure0809A070 closure;
    ValueCallback0809A070 callback;

    callback = func_0809AC6C;
    closure.argument = owner->collection;
    closure.callback = callback;
    func_080C7CC0(owner->collection, func_0809ABE8, &closure);
    func_080C7C48(owner->collection);
}
