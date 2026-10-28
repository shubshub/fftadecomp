#include "ffta.h"

typedef struct {
    void *object;
} Context08027AE8;

Context08027AE8 *func_08096D88(void);
void *func_08096D7C(void);
u32 func_08099544(void *state);
u8 func_080C8240(void *object);
u8 func_080C8260(const void *object);
u8 func_080CED5C(u8 mode);

u8 func_08027AE8(void)
{
    Context08027AE8 *context = func_08096D88();

    if (func_08099544(func_08096D7C()) != 0 &&
        func_080C8240(context->object) == 0 &&
        func_080C8260(context->object) == 0 &&
        func_080CED5C(1) == 0)
        return 1;

    return 0;
}
