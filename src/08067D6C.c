#include "ffta.h"

/* Complete [0x08067D6C, 0x08067E46): 218 bytes, 99 instructions. */
typedef struct {
    u16 first;
    u16 current;
} ScrollPosition;

typedef struct {
    u8 unknown_0000[0xa04];
    ScrollPosition ordinary[8];
    ScrollPosition alternate[1];
} PositionStore;

typedef struct {
    u8 unknown_00[0x1a];
    s16 first;
} ScrollView;

typedef struct {
    u8 unknown_00[0x11];
    u8 current;
} Selector;

typedef struct {
    PositionStore *owner;
    u8 unknown_04[4];
    u8 kind;
    u8 unknown_09;
    u8 count;
    s8 group;
    u8 unknown_0c[4];
    void (*callback)(void);
    u8 unknown_14[0x3c];
    ScrollView view;
    u8 unknown_6c[4];
    Selector selector;
} SelectionState;

extern s16 func_08017BE8(ScrollView *);
extern void func_08141540(s32);
extern void func_080682E4(SelectionState *);
extern void func_08066ED8(SelectionState *);
extern void func_08066C28(SelectionState *);

s8 func_08067D6C(SelectionState *state, u8 direction)
{
    ScrollView *view = &state->view;
    Selector *selector = &state->selector;
    ScrollPosition *saved;
    s32 original, first, total, current, remaining;

    if (state->kind == 4)
        saved = &state->owner->alternate[state->group];
    else
        saved = &state->owner->ordinary[state->kind];
    original = view->first;
    first = original;
    total = func_08017BE8(view) + 1;
    current = selector->current;
    remaining = state->count;
    while (remaining != 0) {
        --remaining;
        if (direction == 0x80) {
            if (first + state->count < total) {
                ++first;
            } else {
                remaining = 0;
                if (original == total - state->count)
                    current = state->count - 1;
            }
        } else {
            if (first > 0) {
                --first;
            } else {
                remaining = 0;
                if (original == 0)
                    current = 0;
            }
        }
    }
    if (original != first || selector->current != current) {
        saved->first = first;
        saved->current = current;
        func_08141540(0x6d);
        if (state->kind == 4)
            func_080682E4(state);
        else
            func_08066ED8(state);
        if (state->callback)
            func_08066C28(state);
    }
    return 0;
}
