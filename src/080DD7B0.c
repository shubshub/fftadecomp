#include "ffta.h"

/* 0x080DD7B0..0x080DD808: 88 bytes / 39 instructions. */
typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ChildPair;

typedef void (*ChildCallback)(void *child, u8 value, u32 a2, u32 a3,
                              u32 a4, u32 a5);
extern ChildCallback const data_08394034[];

void func_080DD7B0(ChildPair *state, u8 value, u8 include_second)
{
    void *first = state->first;
    void *second = state->second;

    if (first != 0)
        data_08394034[0](first, value, 0, 0, 0, 0);
    if (include_second != 0 && second != 0)
        data_08394034[0](second, value, 0, 0, 0, 0);
}
