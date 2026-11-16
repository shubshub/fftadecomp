// 0x08000FC8..0x0800105C: 148 bytes, 68 instructions.
// Finds the current bank's occupied affine-matrix slot holding the same four
// parameters as `matrix`, or claims the first free slot and copies them in.
// Returns the slot index, or 0 when every slot is taken.  Every halfword
// store into the slot table is preceded by a dead load of that halfword and
// the four equality tests stay separate halfword compares: the slot type's
// members are volatile.
#include "ffta.h"

typedef struct {
    volatile u16 pa : 16;
    volatile u16 pb : 16;
    volatile u16 pc : 16;
    volatile u16 pd : 16;
} AffineSlot;

extern u8 data_03000028;
extern u8 data_03003270[][32];
extern AffineSlot data_030032B0[][32];

int func_08000FC8(const AffineSlot *matrix)
{
    u8 *used = data_03003270[data_03000028];
    AffineSlot *slots = data_030032B0[data_03000028];
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
