#include "ffta.h"

struct Sequence08050A8C {
    u8 unknown_00[0x11];
    u8 current;
    u8 unknown_12[2];
};

struct State08050A8C {
    u8 unknown_00[0x48];
    u8 object[0x20];
    struct Sequence08050A8C sequence;
    u8 reset_state[1];
};

extern void func_08017FBC(void *state);
extern void func_08017FB0(struct Sequence08050A8C *sequence, u8 value);
extern void func_080505BC(struct State08050A8C *state, s8 value);
extern void func_08017884(void *object, u32 value, u32 enabled);
extern void func_08050B9C(struct State08050A8C *state, u8 value, u32 mode);

/* Complete [0x08050A8C, 0x08050AF2): 102 bytes, 46 instructions. */
void func_08050A8C(struct State08050A8C *state, u8 object_value,
                   u8 sequence_value, u8 mode)
{
    u32 step = object_value;
    struct Sequence08050A8C *sequence = &state->sequence;
    u8 *reset_state = state->reset_state;
    u8 *object = state->object;

    func_08017FBC(reset_state);
    if (mode == 0) {
        func_08017FB0(sequence, sequence_value);
    } else {
        func_080505BC(state, (s8)sequence_value);
        func_08017884(object, step, 1);
    }
    func_08050B9C(state, sequence->current, 0);
}
