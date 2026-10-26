#include "ffta.h"

typedef struct {
    u8 unknown_00[0x144];
    u8 handle;
} Unit080921B4;

typedef struct {
    Unit080921B4 *unit;
} Context080921B4;

extern void func_08000D90(s32 handle);

/* Complete [0x080921B4, 0x080921C8): 20 bytes, 9 instructions. */
void func_080921B4(Context080921B4 *context)
{
    func_08000D90(context->unit->handle);
}
