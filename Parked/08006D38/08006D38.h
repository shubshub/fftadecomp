#ifndef FFTA_08006D38_H
#define FFTA_08006D38_H

#include "ffta.h"

static inline u8 *decode_owner_link(u8 *owner, const u8 *encoded)
{
    u32 offset = encoded[0] | (encoded[1] << 8);

    return offset != 0 ? owner + offset * 4 : 0;
}

#endif
