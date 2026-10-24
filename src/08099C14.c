/* 0x08099C14, 8 bytes: 827f8177101c7047 */
#include "ffta.h"

u32 func_08099C14(void *object, u32 value)
{
    u8 *bytes = object;
    u32 previous = bytes[0x1E];

    bytes[0x1E] = (u8)value;
    return previous;
}
