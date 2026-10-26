#include "ffta.h"

/* Complete [0x0803938C, 0x08039424): 152 bytes, 65 instructions. */
typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input0803938C;

typedef struct {
    u8 unknown_000[0xF1C];
    u8 count;
    u8 unknown_F1D[2];
    u8 selection;
    u8 displayed_selection;
} State0803938C;

extern Input0803938C data_03000000;
extern State0803938C *g_state_03002810;

u32 func_0803938C(u32 arg0, u32 arg1, u32 arg2, u32 flags)
{
    u32 result = 0;

    if (flags & 1) {
        u16 keys = data_03000000.repeated & 0xC0;

        if (keys & 0x80) {
            if (++g_state_03002810->selection >= g_state_03002810->count) {
                g_state_03002810->selection = g_state_03002810->count - 1;
                result = 2;
            }
        } else if (keys & 0x40) {
            if (--g_state_03002810->selection == 0xFF) {
                g_state_03002810->selection = 0;
                result = 1;
            }
        }
    }
    g_state_03002810->displayed_selection = g_state_03002810->selection;
    return result;
}
