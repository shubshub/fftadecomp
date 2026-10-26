#include "ffta.h"

/* 0x08089B0C..0x08089B48: 60 bytes. */
void func_08089B0C(u16 *tiles, u16 filled, u16 length, u16 tile)
{
    u16 *cursor = tiles;
    u16 empty = length - filled;
    u16 column;

    for (column = 0; column < length; ++column) {
        if (column >= empty)
            *cursor = tile + 0xDB;
        else
            *cursor = 0;
        ++cursor;
    }
}
