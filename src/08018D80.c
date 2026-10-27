#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 identifier;
} TextState;

extern TextState g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern s32 func_080CA7A4(u16 identifier, u8 selector);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08018D80..08018DAC: 44 bytes. */
u32 func_08018D80(u8 *destination)
{
    const u8 *const *strings = g_table_08526680;
    s32 index = func_080CA7A4(g_state_020020D0.identifier, 0);

    func_08018C24(destination, strings[index]);
    return 0;
}
