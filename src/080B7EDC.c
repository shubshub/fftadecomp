#include "ffta.h"

typedef struct {
    u8 unknown_00[0x109];
    u8 first;
    u8 second;
} Struct080B7EDC;

void func_080B7EDC(Struct080B7EDC *source, u8 *first, u8 *second)
{
    *first = source->first;
    *second = source->second;
}
