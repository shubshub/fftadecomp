#include "ffta.h"

/* 0x080D3A88..0x080D3ABE: 54 bytes. */
typedef struct {
    u8 unknown_00[2];
    u16 flags;
} ObjectState;

extern int data_020159C0;
extern ObjectState *func_08005BFC(int index);

void func_080D3A88(u8 enabled)
{
    ObjectState *object = func_08005BFC(data_020159C0);

    if (enabled)
        object->flags &= 0xFFF7;
    else
        object->flags |= 8;
}
