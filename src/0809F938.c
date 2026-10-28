#include "ffta.h"

/* 0x0809F938..0x0809F958: 32 bytes. */
void func_0809DCC4(void *state, s8 *status);

u8 func_0809F938(void *state, s8 *status)
{
    func_0809DCC4(state, status);
    switch (*status) {
    case 2:
    case 3:
    case 4:
        return 1;
    default:
        return 0;
    }
}
