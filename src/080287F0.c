#include "ffta.h"

typedef struct MenuControl080287F0 {
    u8 unknown_00[4];
    u8 mode;
} MenuControl080287F0;

extern const MenuControl080287F0 *data_0200F438;
extern u8 func_080C9540(u16 bit_index);

/* Complete [0x080287F0, 0x08028822): 50 bytes, 21 instructions. */
u8 func_080287F0(void)
{
    if (data_0200F438->mode == 4 &&
        func_080C9540(3) != 0 && func_080C9540(4) == 0)
        return 1;

    return 0;
}
