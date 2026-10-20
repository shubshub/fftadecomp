#include "ffta.h"

void func_08006FCC(void *owner, void *allocation);

void func_08007170(void *owner, u8 *object)
{
    func_08006FCC(owner, object - 12);
}
