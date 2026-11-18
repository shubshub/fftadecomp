#include "ffta.h"

typedef struct {
    const u8 *text;
} TextState;

extern TextState g_state_020020D0;
extern u16 func_08018C24(u8 *destination, const u8 *source);

u32 func_080195F4(u8 *destination, u8 code)
{
    func_08018C24(destination, g_state_020020D0.text);
    return 0;
}
