#include "ffta.h"

typedef struct Resource08019608 {
    u8 unknown_00[0x14];
    u8 value;
} Resource08019608;

extern const Resource08019608 *g_state_020020D0;
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Complete [0x08019608, 0x08019638): 48 bytes, 20 instructions. */
u32 func_08019608(u8 *destination)
{
    const Resource08019608 *resource = g_state_020020D0;
    u8 *cursor = destination;

    if (resource->value < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, resource->value);
    return 0;
}
