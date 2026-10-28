#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x10];
    u32 value;
} CommandState;

extern CommandState *data_0200F454;

/* Complete [0x0806603C, 0x08066048): 12 bytes, 4 reachable instructions. */
void func_0806603C(u32 value)
{
    data_0200F454->value = value;
}
