#include "ffta.h"

/* 0x08050CDC..0x08050CE8: 12 bytes. */
typedef struct {
    u8 unknown_00[0x15];
    u8 value;
} SortRecord08050CDC;

s32 func_08050CDC(const void *first, const void *second)
{
    const SortRecord08050CDC *a = *(const SortRecord08050CDC * const *)first;
    const SortRecord08050CDC *b = *(const SortRecord08050CDC * const *)second;

    return a->value - b->value;
}
