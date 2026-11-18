#ifndef TILE_ANIMATION_H
#define TILE_ANIMATION_H

#include "ffta.h"

/* 0800B394 allocates 40 bytes and links each animation to its layer. */
typedef struct TileAnimation {
    u8 layer;
    u8 status;
    u16 flags;
    s16 timer;
    s16 current;
    u8 origin_x;
    u8 origin_y;
    u16 loop_start;
    u16 end;
    u16 field_0e;
    u16 field_10;
    u8 unknown_12[2];
    const u8 *frames;
    const u8 *entries;
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
    struct TileAnimation *previous;
    struct TileAnimation *next;
} TileAnimation;

#endif
