#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    const u8 *text;
} TextState;

extern TextState g_state_020020D0;
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* Formatter codes 32 and 65 copy the text selected at state offset 8. */
u32 func_08019494(u8 *destination, u8 code)
{
    func_08018C24(destination, g_state_020020D0.text);
    return 0;
}
