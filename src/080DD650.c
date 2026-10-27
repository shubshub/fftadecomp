#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *object;
} State080DD650;

extern u8 func_0809D8B4(void *object);

/* 0x080DD650 - 32 bytes.
 * Target: 00b54068002808d0c0f72cf9011c0906090e48420843c00f00e0002002bc0847
 */
u8 func_080DD650(const State080DD650 *state)
{
    if (state->object == 0)
        return 0;
    return func_0809D8B4(state->object) != 0;
}
