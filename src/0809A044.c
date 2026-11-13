#include "ffta.h"

// Complete target [0x0809A044,0x0809A070): 44 bytes.
// 10b582b0041c074960690090019106496a462df033fe60692df0f4fd02b010bc01bc00476dac0908e9ab0908
typedef struct ListNode0809A044 ListNode0809A044;
typedef struct Collection0809A044 Collection0809A044;

typedef s32 (*ValueCallback0809A044)(void *value, Collection0809A044 *collection);

typedef struct {
    Collection0809A044 *argument;
    ValueCallback0809A044 callback;
} Closure0809A044;

typedef struct {
    u8 unknown_00[0x14];
    Collection0809A044 *collection;
} Owner0809A044;

extern u32 func_0809ABE8(ListNode0809A044 *node, Closure0809A044 *closure);
extern s32 func_0809AC6C(void *object, Collection0809A044 *collection);
extern void func_080C7CC0(Collection0809A044 *list,
                          u32 (*callback)(ListNode0809A044 *, Closure0809A044 *),
                          Closure0809A044 *closure);
extern void func_080C7C48(Collection0809A044 *list);

void func_0809A044(Owner0809A044 *owner)
{
    Closure0809A044 closure;
    ValueCallback0809A044 callback;

    callback = func_0809AC6C;
    closure.argument = owner->collection;
    closure.callback = callback;
    func_080C7CC0(owner->collection, func_0809ABE8, &closure);
    func_080C7C48(owner->collection);
}
