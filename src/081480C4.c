#include "ffta.h"

extern void *func_081471E0(u16 first, u16 last, u16 duration, u16 flags,
                           void *context, void *data);

/* Target: complete [0x081480C4, 0x08148104), 64 bytes.
 * 10b582b01c1c0004000c031c0904090c1204120c591801390904090c07488142
 * 00d9011c009404980190181c0023fff775f802b010bc02bc08470000ff010000
 */
void *func_081480C4(u16 first, u16 count, u16 duration, void *context,
                    void *data)
{
    u16 last = first + count - 1;

    if (last > 511)
        last = 511;
    return func_081471E0(first, last, duration, 0, context, data);
}
