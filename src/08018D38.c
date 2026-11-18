#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u32 value;
} TextState;

extern TextState g_state_020020D0;
extern u16 func_08018ABC(u8 *destination, u32 value);

/* Codes 4, 10, 14, 16, 17 and 58 format the same unsigned value. */
u32 func_08018D38(u8 *destination, u8 code)
{
    func_08018ABC(destination, g_state_020020D0.value);
    return 0;
}
