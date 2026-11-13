#include "ffta.h"

// Complete target [0x0809A018,0x0809A044): 44 bytes.
// 10b582b0041c074920690090019106496a462df049fe20692df00afe02b010bc01bc00476dac0908e9ab0908
typedef struct ListNode0809A018 ListNode0809A018;
typedef struct Collection0809A018 Collection0809A018;

typedef s32 (*ValueCallback0809A018)(void *value, Collection0809A018 *collection);

typedef struct {
    Collection0809A018 *argument;
    ValueCallback0809A018 callback;
} Closure0809A018;

typedef struct {
    u8 unknown_00[0x10];
    Collection0809A018 *collection;
} Owner0809A018;

extern u32 func_0809ABE8(ListNode0809A018 *node, Closure0809A018 *closure);
extern s32 func_0809AC6C(void *object, Collection0809A018 *collection);
extern void func_080C7CC0(Collection0809A018 *list,
                          u32 (*callback)(ListNode0809A018 *, Closure0809A018 *),
                          Closure0809A018 *closure);
extern void func_080C7C48(Collection0809A018 *list);

void func_0809A018(Owner0809A018 *owner)
{
    Closure0809A018 closure;
    ValueCallback0809A018 callback;

    callback = func_0809AC6C;
    closure.argument = owner->collection;
    closure.callback = callback;
    func_080C7CC0(owner->collection, func_0809ABE8, &closure);
    func_080C7C48(owner->collection);
}
