#include "ffta.h"

/* 0x080C7B78..0x080C7B82: 10 bytes. */
typedef struct {
    u32 first;
    u32 second;
} Pair;

void func_080C7B78(const Pair *source, u32 *second, u32 *first)
{
    *second = source->second;
    *first = source->first;
}
