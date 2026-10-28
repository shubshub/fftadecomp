#include "ffta.h"

extern u16 data_04000004;

void func_080033C8(u16 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        while (data_04000004 & 1) {
        }
        while (!(data_04000004 & 1)) {
        }
    }
}
