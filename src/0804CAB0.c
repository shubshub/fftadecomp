#include "ffta.h"

extern u8 *data_0201F540;

/* 0804CAB0..0804CABC: 12 bytes, including the referenced pointer literal. */
u8 *func_0804CAB0(void)
{
    return data_0201F540 + 4;
}
