#include "ffta.h"

struct Group080DD4A4;
struct Child080DD4A4;

extern struct Child080DD4A4 *func_080A8810(struct Group080DD4A4 *group,
                                         s32 index);

struct Child080DD4A4 *func_080DD4A4(struct Group080DD4A4 *group, u8 index)
{
    return func_080A8810(group, index);
}
