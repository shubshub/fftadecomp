#include "ffta.h"

/* Complete [0x0802FB64, 0x0802FB94): 48 bytes: 19 instructions and two
 * literal words.
 * Target: 00b501209ff0f8f80006002801d0002008e000210448054a80180078012800d9
 *         0121081c02bc084700000002323c0000.
 */
typedef struct {
    u8 unknown_00[0x3C32];
    u8 mode;
} State0802FB64;

extern State0802FB64 g_state_02000000;
extern u8 func_080CED5C(u8 mode);

u8 func_0802FB64(void)
{
    if (func_080CED5C(1))
        return 0;
    return g_state_02000000.mode > 1;
}
