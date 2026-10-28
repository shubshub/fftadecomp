#include "ffta.h"

extern u8 g_state_02000000[];

void func_080992E0(void *object, void *state);

void func_0809AB14(void *object)
{
    func_080992E0(object, g_state_02000000);
}
