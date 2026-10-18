#include "ffta.h"

typedef struct {
    u8 unknown_000[0x304];
    u8 (*records)[6][20];
} State0812B538;

u16 func_0812B538(State0812B538 *state, u8 record, u8 index, u8 group)
{
    u8 *value = state->records[record][group] + index * 2;

    return (value[0] << 8) | value[1];
}
