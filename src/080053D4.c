#include "ffta.h"

extern u32 data_03002BB8;
extern u32 data_03002BB4;
extern u32 data_03002BB0;

u16 func_080053D4(const u8 *data)
{
    u32 cleared = 0;
    data_03002BB8 = cleared;
    data_03002BB4 = cleared;
    data_03002BB0 = cleared;
    if (!data)
        return 0;
    return (data[2] << 8) | data[3];
}
