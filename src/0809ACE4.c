#include "ffta.h"

/* 0x0809ACE4..0x0809AD1C: 56 bytes / 24 instructions. */
typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ChildPair;

typedef void (*ChildCallback)(void *child, u8 value);
extern ChildCallback const data_08394054[];

u32 func_0809ACE4(ChildPair *state, u8 value)
{
    if (state->first != 0)
        data_08394054[0](state->first, value);
    if (state->second != 0)
        data_08394054[0](state->second, value);
    return 1;
}
