/* 0x08011634 - 16 bytes: capture a shared word and its address. */
#include "ffta.h"

extern u32 data_02009174;

typedef struct {
    u32 *address;
    u32 value;
} WordSnapshot08011634;

void func_08011634(WordSnapshot08011634 *snapshot)
{
    snapshot->address = &data_02009174;
    snapshot->value = data_02009174;
}
