#include "ffta.h"

/* 0x081342A8..0x081342B4: 12 bytes. */
extern int func_08133F70(const void *, const void *, int);

int func_081342A8(const void *source, const void *target)
{
    return func_08133F70(source, target, 3);
}
