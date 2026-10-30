#include "ffta.h"

extern void *func_08147124(u16 first, u16 last, u16 amount, u16 setting,
                           u16 value, const void *data);

/* Target: complete [0x08148084, 0x081480C4), 64 bytes.
 * 10b582b00004000c041c0904090c1204120c1b041b0c611801390904090c0748
 * 814200d9011c009304980190201c0023fff736f802b010bc02bc0847ff010000
 */
void *func_08148084(u16 first, u16 count, u16 amount, u16 value,
                    const void *data)
{
    u16 last = first + count - 1;

    if (last > 511)
        last = 511;
    return func_08147124(first, last, amount, 0, value, data);
}
