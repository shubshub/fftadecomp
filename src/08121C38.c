#include "ffta.h"

/* Target: complete [0x08121C38, 0x08121C58), 32 bytes, 13 instructions.
 * This is an offset view; the original object's complete extent is unknown. */
typedef struct {
    u8 unknown_00[0x54];
    void *object;
} State08121C38;

extern State08121C38 *data_020159CC;
extern u8 func_0809D2F8(void *object);

u32 func_08121C38(void)
{
    u32 result;

    if (data_020159CC->object == 0)
        result = 1;
    else
        result = func_0809D2F8(data_020159CC->object);
    return result;
}
