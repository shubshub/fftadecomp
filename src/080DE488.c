#include "ffta.h"

/* 0x080DE488..0x080DE49E: 22 bytes. */
extern u8 func_0809A3BC(void);

int func_080DE488(void)
{
    if (func_0809A3BC())
        return 1;
    return 0;
}
