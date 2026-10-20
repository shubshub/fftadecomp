#ifndef FFTA_0801CDA4_H
#define FFTA_0801CDA4_H

#include "ffta.h"

static inline void read_map_dimensions(u8 *width, u8 *height, u8 *left, u8 *top)
{
    const u8 *state = (const u8 *)0x02007F10;

    *width = state[0xD];
    *height = state[0xF];
    *left = state[0xA];
    *top = state[0xC];
}

static inline void read_map_edges(u8 *upper, u8 *lower)
{
    const u8 *state = (const u8 *)0x02007F10;

    *upper = state[0xE];
    *lower = state[0xB];
}

#endif
