#include "ffta.h"

typedef struct TextState {
    u8 unknown_0000[0x21C6];
    u8 text_index;
} TextState;

extern TextState g_state_02000000;
extern const u8 *const data_08569034[];
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 0801928C..080192C0: 52 bytes, 18 instructions. */
u32 func_0801928C(u8 *destination)
{
    if (g_state_02000000.text_index != 0)
        func_08018C24(destination, data_08569034[g_state_02000000.text_index]);
    return 0;
}
