/* 0x080DD580: 00b58089c009012100220840012800d10122101c02bc0847 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} State080DD580;

static inline u8 object_enabled_flag(const State080DD580 *object)
{
    return (object->flags >> 7) & 1;
}

u8 func_080DD580(const State080DD580 *object)
{
    /* No instruction shows the sign of this flag; the bytes need it read into
       a narrow signed local before the comparison. */
    s8 temp = object_enabled_flag(object);

    u8 result = 0;
    if (temp == 1)
        result = 1;
    return result;
}
