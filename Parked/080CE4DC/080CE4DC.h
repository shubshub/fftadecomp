#ifndef FUNCTION_080CE4DC_H
#define FUNCTION_080CE4DC_H

#include "ffta.h"

static inline u16 read_record_u16(const u8 *bytes)
{
    return bytes[0] | (bytes[1] << 8);
}

#endif
