#include "positioned_equipment.h"

/* 0x0812E0BC..0x0812E0FA: 62 bytes. */
extern s32 func_0812DBA8(const void *, const void *, u16, u32);

s32 func_0812E0BC(const void *source, const void *target,
                   u16 item, u8 mode, u32 flags)
{
    s32 result;

    if (item == 0)
        result = func_0812C8DC(source, target, mode, 0);
    else
        result = func_0812DBA8(source, target, item, flags);
    if (result != 0 && func_080CDA64(target))
        result = 100;
    return result;
}
