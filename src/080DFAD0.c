#include "ffta.h"

/* 0x080DFAD0..0x080DFAEC: 28 bytes. */
typedef struct {
    u8 unknown_00[6];
    u16 flags;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

int func_080DFAD0(int index)
{
    if (func_08005BFC(index)->flags & 0x8000)
        return 1;
    return 0;
}
