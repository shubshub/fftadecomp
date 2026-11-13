#include "ffta.h"

// Complete [0x0809A548, 0x0809A570): 40 bytes.
// 00b584b00091019205496a46029202aa5160006903492df0affb04b001bc0047a5ac0908e9ab0908
typedef struct ListNode0809A548 ListNode0809A548;
typedef struct ListContext0809A548 ListContext0809A548;
typedef struct Object0809A548 Object0809A548;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809A548 *list;
} Owner0809A548;

typedef struct {
    u32 clear_mask;
    u32 set_mask;
} FlagChange0809A548;

typedef u32 (*ObjectCallback0809A548)(Object0809A548 *object,
                                      const FlagChange0809A548 *change);

typedef struct {
    const FlagChange0809A548 *argument;
    ObjectCallback0809A548 callback;
} Closure0809A548;

extern u32 func_0809ABE8(ListNode0809A548 *node, Closure0809A548 *closure);
extern u32 func_0809ACA4(Object0809A548 *object, const FlagChange0809A548 *change);
extern void func_080C7CC0(ListContext0809A548 *list,
                          u32 (*callback)(ListNode0809A548 *, Closure0809A548 *),
                          Closure0809A548 *closure);

void func_0809A548(Owner0809A548 *owner, u32 clear_mask, u32 set_mask)
{
    FlagChange0809A548 change;
    Closure0809A548 closure;
    ObjectCallback0809A548 callback;

    change.clear_mask = clear_mask;
    change.set_mask = set_mask;
    callback = func_0809ACA4;
    closure.argument = &change;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
}
