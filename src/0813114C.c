#include "ffta.h"

/* 0x0813114C..0x08131160: 20 bytes, 9 instructions. */
typedef struct {
    u32 first;
    u32 second;
} Arguments;

extern u32 func_0812F068(u32 first, u32 second);

u8 func_0813114C(const Arguments *arguments)
{
    return func_0812F068(arguments->first, arguments->second);
}
