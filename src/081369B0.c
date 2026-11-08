#include "ffta.h"

/* Target: [0x081369B0, 0x081369EC), 60 bytes, 29 instructions. */
s32 func_081369B0(s16 start, s16 end, u16 duration, u16 elapsed)
{
    if (elapsed >= duration)
        return end;
    start += (end - start) * elapsed / duration;
    return start;
}
