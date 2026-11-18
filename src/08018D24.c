#include "ffta.h"

extern u8 g_state_020021A0[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* Formatter slot 3 copies the text beginning at 020021A0. */
u32 func_08018D24(u8 *destination, u8 code)
{
    func_08018C24(destination, g_state_020021A0);
    return 0;
}
