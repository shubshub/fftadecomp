#include "ffta.h"

// Complete target [0x0809AA38,0x0809AA92): 90 bytes.
// 70b591b009060e0e00210d910da96a464a600b4b0f910faa5360006909492df033f90d9c
// 0023a34212da82256d006a461168086840190078b04205d1081c08e021ac0908e9ab0908
// 04320133a342efdb002011b070bc02bc0847
typedef struct ListNode0809AA38 ListNode0809AA38;
typedef struct ListContext0809AA38 ListContext0809AA38;

typedef struct {
    u8 unknown_000[0x104];
    u8 id;
} Record0809AA38;

typedef struct {
    Record0809AA38 *record;
} Unit0809AA38;

typedef struct {
    s32 count;
    Unit0809AA38 **cursor;
} State0809AA38;

typedef u32 (*ValueCallback0809AA38)(void *value, State0809AA38 *argument);

typedef struct {
    State0809AA38 *argument;
    ValueCallback0809AA38 callback;
} Closure0809AA38;

typedef struct {
    u8 unknown_00[0x10];
    ListContext0809AA38 *list;
} Owner0809AA38;

extern u32 func_0809ABE8(ListNode0809AA38 *node, Closure0809AA38 *closure);
extern u32 func_0809AC20(void *value, State0809AA38 *state);
extern void func_080C7CC0(ListContext0809AA38 *list,
                          u32 (*callback)(ListNode0809AA38 *, Closure0809AA38 *),
                          Closure0809AA38 *closure);

Unit0809AA38 *func_0809AA38(Owner0809AA38 *owner, u8 id)
{
    Unit0809AA38 *units[13];
    State0809AA38 state;
    Closure0809AA38 closure;
    ValueCallback0809AA38 callback;
    s32 count;
    s32 i;

    state.count = 0;
    state.cursor = units;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);
    count = state.count;
    for (i = 0; i < count; i++) {
        if (units[i]->record->id == id)
            return units[i];
    }
    return 0;
}
