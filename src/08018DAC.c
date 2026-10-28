#include "ffta.h"

typedef struct TextState {
    u8 unknown_00[0x0E];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *g_table_08526680[];
extern u16 func_080CA7A4(u16 identifier, u32 mode);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018DAC..08018DF0: 68 bytes, 26 instructions. */
u32 func_08018DAC(u8 *destination)
{
    u16 index;

    if (g_state_020020D0.identifier <= 0x178)
        index = func_080CA7A4(g_state_020020D0.identifier, 0);
    else
        index = g_state_020020D0.identifier + 0x7B;
    func_08018C24(destination, g_table_08526680[index]);
    return 0;
}
