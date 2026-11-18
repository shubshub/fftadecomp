#include "ffta.h"

typedef struct AffineMatrix {
    s16 pa, pb, pc, pd;
} AffineMatrix;

extern u8 data_03000028;
extern u8 data_03003270[2][32];
extern AffineMatrix data_030032B0[2][32];

int func_08000FC8(const volatile AffineMatrix *matrix)
{
    u8 *used = data_03003270[data_03000028];
    volatile AffineMatrix *slots = data_030032B0[data_03000028];
    int index;

    for (index = 0; index < 32; index++) {
        if (used[index] && matrix->pa == slots[index].pa &&
            matrix->pb == slots[index].pb && matrix->pc == slots[index].pc &&
            matrix->pd == slots[index].pd)
            return index;
    }
    for (index = 0; index < 32; index++) {
        if (!used[index]) {
            used[index] = 1;
            slots[index].pa = matrix->pa;
            slots[index].pb = matrix->pb;
            slots[index].pc = matrix->pc;
            slots[index].pd = matrix->pd;
            return index;
        }
    }
    return 0;
}
