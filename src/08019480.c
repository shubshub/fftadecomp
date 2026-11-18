#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern u16 func_08018ABC(u8 *destination, u32 value);

u32 func_08019480(u8 *destination, u8 code)
{
    func_08018ABC(destination, g_state_020020D0.identifier);
    return 0;
}
