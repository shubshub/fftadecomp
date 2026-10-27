#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *func_080CB524(u32 identifier);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018E94..08018EB4: 32 bytes, 12 instructions. */
u32 func_08018E94(u8 *destination)
{
    func_08018C24(destination, func_080CB524(g_state_020020D0.identifier));
    return 0;
}
