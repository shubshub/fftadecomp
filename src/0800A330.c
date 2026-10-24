#include "ffta.h"

/* 0x0800A330 - 60 bytes including the literal pool.
 * Target: 10b5041c0b1c0b480b4a8118088800280dd0021c59789878000201438a4206d1
 *         d97818790002014360880918618010bc01bc0047000000029e210000
 */
typedef struct {
    u16 unknown_00;
    u16 position;
} ScriptContext0800A330;

typedef struct {
    u8 unknown_0000[0x219E];
    u16 value;
} State0800A330;

extern State0800A330 g_state_02000000;

void func_0800A330(ScriptContext0800A330 *context, const u8 *instruction)
{
    if (g_state_02000000.value != 0 &&
        g_state_02000000.value == (instruction[1] | (instruction[2] << 8)))
        context->position += instruction[3] | (instruction[4] << 8);
}
