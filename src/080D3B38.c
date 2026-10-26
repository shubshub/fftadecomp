#include "ffta.h"

/* 0x080D3B38..0x080D3B52: 26 bytes. */
typedef struct {
    u8 unknown_00[4];
    u16 flags;
} ObjectState;

extern ObjectState *func_080A880C(void);

u8 func_080D3B38(void)
{
    if (func_080A880C()->flags & 8)
        return 1;
    return 0;
}
