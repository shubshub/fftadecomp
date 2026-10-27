#include "ffta.h"

/* 0x0813079C..0x081307C8: 44 bytes. */
extern int func_0812FE38(void *, void *, u16, u16, u16, u8, int);

int func_0813079C(void *source, void *target, u16 entry,
                   u16 first, u16 second, u8 mode)
{
    return func_0812FE38(source, target, entry, first, second, mode, 0);
}
