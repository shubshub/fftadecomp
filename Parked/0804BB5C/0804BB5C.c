#include "ffta.h"

extern void func_0804BBC0(u8 start, u8 *distance, u8 *previous);

/* 0x0804BB5C..0x0804BBC0: a 32-byte array first stores distances, then the reverse path. */
u8 func_0804BB5C(s32 start, s32 destination, u8 *previous)
{
    u8 distance[32];
    u8 *path;
    s32 current;
    s32 length;

    if (destination == start)
        return 0;
    path = previous;
    func_0804BBC0(start, distance, previous);
    if (distance[destination] == 0xFF)
        return 0;
    length = 0;
    current = destination;
    do {
        distance[length] = current;
        current = path[current];
        length++;
    } while (current != start);
    distance[length] = current;
    for (current = 0; length >= 0; current++, length--)
        path[current] = distance[length];
    return current - 1;
}
