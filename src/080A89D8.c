#include "ffta.h"

typedef struct {
    u8 unknown_00[12];
} Entry080A89D8;

typedef struct {
    Entry080A89D8 entries[16];
    u8 unknown_c0;
    u8 count;
} State080A89D8;

extern State080A89D8 data_0200F8C0;
extern u8 func_080A6F20(u32 input);
extern u8 func_080C9540(u16 flag);
extern void func_080C9574(u16 flag, u16 value);
extern u8 func_080A780C(Entry080A89D8 *entry, s32 arg1, s32 arg2, s32 mode);

/* Complete [0x080A89D8, 0x080A8A54): 124 bytes, 55 instructions. */
State080A89D8 *func_080A89D8(State080A89D8 *context, u32 input, u8 *changed)
{
    State080A89D8 *state = &data_0200F8C0;

    if (context)
        state = context;
    if (func_080A6F20(input)) {
        s32 saved_flag = func_080C9540(0x42);

        func_080C9574(0x42, saved_flag ^ 1);
        *changed = 1;
        if (func_080A780C(&state->entries[state->count], 0, 0, 3))
            state->count++;
        func_080C9574(0x42, saved_flag);
    }
    if (!state->count)
        return 0;
    return state;
}
