#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *rows;
    u8 unknown_10[5];
    u8 count;
} Rows08058104;

extern u16 data_02003CB0[];
extern void func_0814186C(const void *source, void *destination, u32 size);
extern void func_08057E98(Rows08058104 *state, u8 value, u8 first, u8 second);

/* 0x08058104..0x080581AA: 166 bytes, including the literal pool. */
void func_08058104(Rows08058104 *state, u8 first, u8 second,
                   u8 value, u16 direction)
{
    u16 *scratch = data_02003CB0;
    u32 count = state->count * 5;
    u32 bytes;

    if (direction == 0x80) {
        bytes = count * 2;
        func_0814186C(state->rows + count, scratch, bytes);
        func_0814186C(scratch, state->rows, bytes);
        func_08057E98(state, value, first, second);
        return;
    }
    if (direction == 0x40) {
        bytes = count * 2;
        func_0814186C(state->rows, scratch, bytes);
        func_0814186C(scratch, state->rows + count, bytes);
        func_08057E98(state, value, first, second);
    }
}
