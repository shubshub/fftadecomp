#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 value;
} ObjectState;

extern ObjectState *func_08005BFC(int index);

void func_080D47C8(int index, u16 value)
{
    func_08005BFC(index)->value = value;
}
