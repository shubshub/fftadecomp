#include "ffta.h"

/* 0x08004FF4..0x08005028: 52 bytes, 20 instructions. */
extern const char data_03002892[];
extern u32 func_081444B8(const char *string);
extern s32 func_081443B0(const char *left, const char *right, u32 count);

u32 func_08004FF4(const char *string)
{
    if (func_081444B8(string) <= 1) {
        return 0;
    }
    if (func_081443B0(string, data_03002892, func_081444B8(string)) == 0) {
        return 1;
    }
    return 0;
}
