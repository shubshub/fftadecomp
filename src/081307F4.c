#include "ffta.h"

typedef struct Unit Unit;
extern s32 func_0812FE38(const Unit *source, const Unit *target,
                         u16 identifier, u16 value, u16 parameter,
                         u8 option, u8 mode);

/* Complete [0x081307F4, 0x08130820): 44 bytes, 21 instructions. */
s32 func_081307F4(const Unit *source, const Unit *target,
                   u16 identifier, u16 value, u16 parameter, u8 option)
{
    return func_0812FE38(source, target, identifier, value, parameter,
                         option, 2);
}
