#include "ffta.h"

extern void *func_080DD47C(void *object);
extern void func_080DBED4(u32 kind, u32 enabled, u32 value, void *object);

void func_080EDB80(void *object)
{
    void *target = func_080DD47C(object);
    func_080DBED4(5, 1, 0, target);
}
