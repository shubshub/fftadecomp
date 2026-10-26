#include "ffta.h"

/* 0x08054284 .. 0x08054312: 142 bytes, 62 instructions. */
typedef struct {
    u8 unknown_00[0x0c];
    u8 *buffer;
    u8 unknown_10[5];
    u8 width;
} State08054284;

extern u8 data_02003CB0[];
extern void func_0814186C(void *, void *, u32);
extern void func_08053F08(State08054284 *, u8, u16);

void func_08054284(State08054284 *state, u16 position, u8 row, u16 direction)
{
    u8 *scratch = data_02003CB0;
    int stride = state->width * 3;

    if (direction == 0x80) {
        func_0814186C(state->buffer + stride * 2, scratch, stride * 3);
        func_0814186C(scratch, state->buffer, stride * 3);
        func_08053F08(state, row, position);
    } else if (direction == 0x40) {
        func_0814186C(state->buffer, scratch, stride * 3);
        func_0814186C(scratch, state->buffer + stride * 2, stride * 3);
        func_08053F08(state, row, position);
    }
}
