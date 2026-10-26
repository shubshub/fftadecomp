#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    const void *object;
} Context08099C9C;

extern u16 func_08021DE0(const void *object);

/* Complete [0x08099C9C, 0x08099CB8): 28 bytes, 13 instructions. */
u8 func_08099C9C(Context08099C9C *context)
{
    if (func_08021DE0(context->object) & 0x100)
        return 1;
    return 0;
}
