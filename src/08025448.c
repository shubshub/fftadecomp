#include "ffta.h"

/* 0x08025448..0x08025464: 28 bytes. */
typedef struct {
    u8 unknown_00[3];
    u8 enabled;
} State08025448;

extern State08025448 *data_0200F438;
extern void func_080253B0(u8 selector, u32 mode);

void func_08025448(u8 selector)
{
    data_0200F438->enabled = 1;
    func_080253B0(selector, 0);
}
