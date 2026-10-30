#include "ffta.h"

struct Context;

extern struct Context data_02010060;
extern u32 func_080BA8E4(struct Context *context);

/* 0x080BC798..0x080BC7AC: 20 complete bytes, including the mapped-data literal. */
u8 func_080BC798(void)
{
    return func_080BA8E4(&data_02010060);
}
