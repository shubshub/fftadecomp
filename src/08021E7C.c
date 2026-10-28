#include "ffta.h"

struct ListNode08021E7C {
    void *value;
    struct ListNode08021E7C *previous;
    struct ListNode08021E7C *next;
};

struct ListContext08021E7C {
    void *owner;
    struct ListNode08021E7C *head;
};

typedef u32 (*ListCallback08021E7C)(struct ListNode08021E7C *node, void *payload);

struct State08021E7C {
    u32 unknown_00;
    struct ListContext08021E7C *first;
    struct ListContext08021E7C *second;
    u8 unknown_0C[8];
    u8 context[0x1C0];
    u16 slots[3];
    u16 unknown_1DA;
    s16 current;
    u16 active;
    u32 unknown_1E0;
    void *pending;
};

extern struct ListNode08021E7C *func_080C7BF4(struct ListContext08021E7C *list,
                                            void *value);
extern void func_080C7CC0(struct ListContext08021E7C *list,
                          ListCallback08021E7C callback, void *payload);
extern void func_080C7CE4(struct ListContext08021E7C *list,
                          struct ListNode08021E7C *start,
                          ListCallback08021E7C callback, void *payload);
extern u32 func_08021484(struct ListNode08021E7C *node, void *payload);
extern u32 func_08022128(struct ListNode08021E7C *node, void *payload);

/* Complete [0x08021E7C, 0x08021F18): 156 bytes, 66 instructions. */
void func_08021E7C(struct State08021E7C *state)
{
    state->active = 0;
    if (state->current > 2)
        state->current = 0;
    {
        struct ListNode08021E7C *node = state->pending;

        if (node != 0) {
            node = func_080C7BF4(state->second, state->pending);
            if (node == 0)
                state->pending = 0;
        }
        if (node == 0) {
            func_080C7CC0(state->second, func_08021484, state->context);
        } else {
            state->pending = 0;
            func_080C7CE4(state->second, node, func_08021484, state->context);
        }
    }
    func_080C7CC0(state->first, func_08022128, 0);
    state->current++;
    if (state->current > 2)
        state->current = 0;
    state->slots[state->current] = 0;
}
