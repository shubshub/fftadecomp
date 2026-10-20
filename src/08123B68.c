#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F69];
    u8 selector;
} ScriptSelectionState;

extern ScriptSelectionState g_state_02000000;

u8 func_08036350(u8 selector);

u32 func_08123B68(u16 *context, const u8 *script)
{
    u8 matched = 0;
    u8 selected = func_08036350(g_state_02000000.selector);

    if (script[1] == 0) {
        u8 index;

        for (index = 1; index <= 6; index++) {
            if (selected == index) {
                matched = 1;
                break;
            }
        }
    } else if (selected == script[1]) {
        matched = 1;
    }
    if (matched)
        *context += script[2] | (script[3] << 8);
    return 0x110;
}
