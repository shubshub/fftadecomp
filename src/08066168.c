#include "ffta.h"

typedef struct {
    u8 unknown_000[0xBAC];
    u32 value;
} State08066168;

extern State08066168 *data_0200F454;

/* Complete target: [0x08066168, 0x0806617C), 20 bytes, 6 instructions. */
void func_08066168(u32 value)
{
    data_0200F454->value = value;
}
