#include "ffta.h"

struct State08017AD8 {
    u8 unknown_00[0x15];
    u8 value_15;
    u8 unknown_16[4];
    u16 amount;
};

extern void func_08017618(struct State08017AD8 *state, u8 value);
extern void func_08017734(struct State08017AD8 *state, u16 amount);

void func_08017AD8(struct State08017AD8 *state)
{
    func_08017618(state, state->value_15);
    func_08017734(state, state->amount * 2);
}
