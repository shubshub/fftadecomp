#include "ffta.h"

/* Target: complete [0x0812F8A4, 0x0812F8E8), 68 bytes. */
extern u32 func_080CCD50(u16 id, u8 field);
extern u32 func_080CA7A4(u16 id, u8 field);

u16 func_0812F8A4(void *context, u16 id, u16 fallback_id)
{
    if (id != 0) {
        u16 result = func_080CCD50(id, 1);

        if (result != 0)
            return result;
        if (func_080CCD50(id, 3) == 0)
            return 0;
    }
    if (fallback_id != 0)
        return func_080CA7A4(fallback_id, 4);
    return 0;
}
