/* func_0800A654 - 0x0800A654, 20 bytes (16 code + 4 literal pool)
 *
 * Allocates `size` bytes out of the game's owner block and returns the
 * block.  The owner is the global pointer kept at 0x02008FF4: func_080070C8
 * stores it there, func_0800A61C clears it again, and func_08007138 does the
 * allocation from it.  This wrapper only supplies that owner.
 *
 *   00b5 011c 0248 0068 fcf76cfd 02bc 0847
 *   pool 0x0800A664: 0x02008FF4
 */

#include "ffta.h"

void *func_08007138(void *owner, u32 size);

void *func_0800A654(u32 size)
{
    void *owner = *(void **)0x02008FF4;

    return func_08007138(owner, size);
}
