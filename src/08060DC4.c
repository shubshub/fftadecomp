#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    s16 value;
} State08060DC4;

extern State08060DC4 *data_0200F44C;

/* 0x08060DC4..0x08060DD4: 16 bytes, including alignment and the pointer literal. */
s16 func_08060DC4(void)
{
    return data_0200F44C->value;
}
