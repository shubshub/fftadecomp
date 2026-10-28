#include "ffta.h"

/* 0x08013858..0x08013890: 56 bytes. */
typedef struct MatrixState MatrixState;
extern void func_08013800(MatrixState *state, u32 column);

void func_08013858(MatrixState *state, s32 first, s32 count)
{
    s32 column;

    if (count == 0) {
        for (column = 0; column < 6; column++) {
            func_08013800(state, column);
        }
    } else {
        for (column = first; column < first + count; column++) {
            func_08013800(state, column);
        }
    }
}
