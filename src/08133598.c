#include "ffta.h"

/* Complete 0x08133598..0x081335BE: 38 bytes, 16 instructions. */
typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} State08133598;

extern u32 func_08002804(void);
extern void func_0802DA00(u8 value);

void func_08133598(State08133598 *state)
{
    if (!(state->flags & 0x10))
        func_0802DA00((s16)func_08002804() % 20);
}
