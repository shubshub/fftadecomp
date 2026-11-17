#include "ffta.h"

// Complete target [0x08099A70, 0x08099BAC): 316 bytes.
typedef struct ListContext08099A70 ListContext08099A70;

typedef struct {
    u8 unknown_00[0xD0];
    s16 priority;
} Record08099A70;

typedef struct {
    Record08099A70 *record;
    u8 unknown_04[0x5C - 4];
    s16 order;
} Entry08099A70;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099A70 *list;
} Owner08099A70;

typedef struct {
    u32 count;
    Entry08099A70 **cursor;
} State08099A70;

typedef u32 (*Callback08099A70)(void *value, void *argument);

typedef struct {
    void *argument;
    Callback08099A70 callback;
} Closure08099A70;

extern u32 func_0809ABE8(void *node, Closure08099A70 *closure);
extern u32 func_0809AC20(void *value, State08099A70 *state);
extern u32 func_0809AD94(void *value, Entry08099A70 *excluded);
extern void func_080C7CC0(ListContext08099A70 *list,
                          u32 (*callback)(void *, Closure08099A70 *),
                          Closure08099A70 *closure);
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern void func_0809F78C(Owner08099A70 *owner, Entry08099A70 **entries, u16 steps);

void func_08099A70(Owner08099A70 *owner, Entry08099A70 *excluded)
{
    Closure08099A70 first;
    State08099A70 state;
    Closure08099A70 second;
    Callback08099A70 callback;
    Entry08099A70 **entries;
    Entry08099A70 *tmp;
    s32 next;
    s32 i;
    s32 j;
    s32 count;
    s32 last;

    callback = (Callback08099A70)func_0809AD94;
    first.argument = excluded;
    first.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &first);
    entries = func_08022840(0x50);
    func_0809F78C(owner, entries, 20);
    next = 0;
    if (excluded != 0) {
        excluded->order = 0;
        next = 1;
    }
    for (i = 0; i < 20; i++) {
        Entry08099A70 *unit = entries[i];
        if (unit->order == -2) {
            unit->order = next;
            next++;
        }
    }
    state.count = 0;
    state.cursor = entries;
    callback = (Callback08099A70)func_0809AC20;
    second.argument = &state;
    second.callback = callback;
    func_080C7CC0(owner->list, func_0809ABE8, &second);
    count = state.count;
    if (next < count) {
        last = count - 1;
        for (i = 0; i < last; i++) {
            for (j = i + 1; j < count; j++) {
                if (entries[i]->record->priority < entries[j]->record->priority) {
                    tmp = entries[i];
                    entries[i] = entries[j];
                    entries[j] = tmp;
                }
            }
        }
        for (i = 0; i < count; i++) {
            Entry08099A70 *unit = entries[i];
            if (unit->order == -2) {
                unit->order = next;
                next++;
            }
        }
    }
    func_08022854(entries);
}
