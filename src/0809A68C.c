#include "ffta.h"

typedef struct {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} Children0809A68C;

extern void (*data_08394054)(void *object, u8 value);

/* 0x0809A68C: 56 bytes; forward a byte value to each existing child. */
void func_0809A68C(Children0809A68C *state, u8 value)
{
    if (state->first)
        data_08394054(state->first, value);
    if (state->second)
        data_08394054(state->second, value);
}
