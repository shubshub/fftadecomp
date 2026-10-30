#include "ffta.h"

extern u8 data_020101F8[];
extern u32 func_080C045C(void *state);

/* 0x080C1438..0x080C144C: 20 bytes, including the named-object literal. */
u8 func_080C1438(void)
{
    return func_080C045C(data_020101F8);
}
