#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 state;
    u8 unknown_119A[3];
    u8 selection;
} MenuState;

extern MenuState *data_0200F448;
extern u8 data_030008B0[];
extern void func_08029E48(void *graphics, void *source, const u16 *scratch,
                          s16 width, s16 height, u8 enabled);

/* Complete [0x0805D4EC, 0x0805D534): 72 bytes, 27 reachable instructions. */
u32 func_0805D4EC(void)
{
    data_0200F448->selection = 0x3F;
    func_08029E48(data_030008B0, 0, 0, 20, 17, 1);
    data_0200F448->state = 0;
    return 2;
}
