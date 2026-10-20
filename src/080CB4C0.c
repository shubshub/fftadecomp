#include "ffta.h"

void func_080CAF78(void *object, u16 entry, u8 slot);

void func_080CB4C0(void *object)
{
    s32 index;

    for (index = 0; index < 5; index++)
        func_080CAF78(object, 0, index);
}
