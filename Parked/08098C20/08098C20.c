#include "ffta.h"

// Complete target [0x08098C20,0x08098CE8): 200 bytes, 100 instructions.
typedef struct ListNode08098C20 ListNode08098C20;
typedef struct ListContext08098C20 ListContext08098C20;

typedef struct {
    u8 unknown_00[0xE7];
    u8 unknown_E7;
    u8 unknown_E8[0xF6 - 0xE8];
    u8 unknown_F6;
    u8 unknown_F7;
    u8 unknown_F8[0x104 - 0xF8];
    u8 unknown_104;
} Unit08098C20;

typedef struct {
    Unit08098C20 *unit;
} Entry08098C20;

typedef struct {
    u32 count;
    Entry08098C20 **cursor;
} State08098C20;

typedef u32 (*ValueCallback08098C20)(void *value, State08098C20 *argument);

typedef struct {
    State08098C20 *argument;
    ValueCallback08098C20 callback;
} Closure08098C20;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08098C20 *list;
} Owner08098C20;

extern u32 func_0809ABE8(ListNode08098C20 *node, void *closure);
extern u32 func_0809AC20(void *value, State08098C20 *state);
extern void func_080C7CC0(ListContext08098C20 *list,
                          u32 (*callback)(ListNode08098C20 *, void *),
                          Closure08098C20 *closure);

void func_08098C20(Owner08098C20 *owner)
{
    Entry08098C20 *entries[13];
    State08098C20 state;
    Closure08098C20 closure;
    ValueCallback08098C20 callback;
    int count;
    int last;
    int i;
    int j;

    state.count = 0;
    state.cursor = entries;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &closure);

    count = state.count;
    last = count - 1;
    for (i = 0; i < last; i++) {
        for (j = i + 1; j < count; j++) {
            if ((entries[i]->unit->unknown_F6 << 8) + entries[i]->unit->unknown_F7
                < (entries[j]->unit->unknown_F6 << 8) + entries[j]->unit->unknown_F7) {
                Entry08098C20 *tmp = entries[i];

                entries[i] = entries[j];
                entries[j] = tmp;
            }
        }
    }

    for (i = 0; i < count; i++) {
        entries[i]->unit->unknown_104 = i;
        entries[i]->unit->unknown_E7 |= 0xFF;
    }
}
