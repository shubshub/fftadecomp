/* 0x080098C4..0x080098F4: run the four registered callback slots (48 bytes). */
#include "ffta.h"

typedef u16 (*TaskCallback)(u32 context);

/* Four two-word records: [0] context, [1] callback (func_080098F4 fills them). */
extern u32 g_state_03000890[][2];

void func_080098C4(u8 outer_index, u8 *outer_flag)
{
    s32 index;

    for (index = 0; index < 4; index++) {
        u32 *record = g_state_03000890[index];

        if (record[1] != 0 && ((TaskCallback)record[1])(record[0]) != 0)
            record[1] = 0;
    }
}
