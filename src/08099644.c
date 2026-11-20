#include "movement_tile.h"

/* 0x08099644..0x0809966C: complete 40-byte owner. */
Actor *func_08099644(Scene *owner, s8 x, s8 z)
{
    TileSearch context;

    context.match = 0;
    context.x = x;
    context.y = z;
    func_080C7CC0(owner->objects, func_0809ABB0, &context);
    return context.match;
}
