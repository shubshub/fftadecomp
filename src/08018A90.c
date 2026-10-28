#include "ffta.h"

extern u8 *data_02009190;
extern u8 func_08017180(u8 *region);

/* 08018A90..08018AA8: 24 bytes. */
u8 func_08018A90(void)
{
    return func_08017180(data_02009190 + 0x14);
}
