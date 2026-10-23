#include "ffta.h"

/* 0x0800A490 - 90 bytes including two internal literal words. */
typedef struct {
    u16 unknown_00;
    u16 position;
} ScriptContext0800A490;

extern u8 g_state_02000000[];

u8 func_08036350(u8 value);

void func_0800A490(ScriptContext0800A490 *context, const u8 *instruction)
{
    int matched = 0;
    u8 selected = func_08036350(g_state_02000000[0x1F69]);
    u8 index;

    if (instruction[1] == 0) {
        for (index = 1; index <= 6; index++) {
            if (selected == index) {
                matched = 1;
                break;
            }
        }
    } else if (selected == instruction[1]) {
        matched = 1;
    }
    if (matched)
        context->position += instruction[2] | (instruction[3] << 8);
}
