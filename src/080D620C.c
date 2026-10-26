#include "ffta.h"

/* 0x080D620C..0x080D621E: 18 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 value;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

void func_080D620C(int index, u16 value)
{
    func_08005BFC(index)->value = value;
}
