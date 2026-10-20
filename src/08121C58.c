#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 mapValue;
    u8 unknown_03;
} CoordinateEntry;

typedef struct {
    CoordinateEntry entries[32];
    s32 count;
} CoordinateList;

CoordinateList *func_08121C58(u8 selector)
{
    u8 **state = (u8 **)0x020159CC;
    u32 offset = 0x58 + selector * sizeof(CoordinateList);

    return (CoordinateList *)(*state + offset);
}
