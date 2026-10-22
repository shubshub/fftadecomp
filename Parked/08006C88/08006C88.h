#include "ffta.h"

static inline u16 read_block_field(const u8 *bytes)
{
    return bytes[0] | (bytes[1] << 8);
}

static inline u8 *decode_block_offset(u8 *owner, u16 offset)
{
    if (offset != 0)
        return owner + offset * 4;
    return 0;
}
