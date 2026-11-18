#include "ffta.h"

extern u8 data_02001F1C[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* Formatter slot 0 copies the text beginning at 02001F1C. */
u32 func_08018D10(u8 *destination, u8 code)
{
    func_08018C24(destination, data_02001F1C);
    return 0;
}
