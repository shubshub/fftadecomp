#include "ffta.h"

/* 0x08044038 .. 0x0804409C: 100 bytes. */
typedef struct {
    u8 active : 1;
    u8 pending : 1;
    u8 unknown_00 : 6;
    u8 unknown_01[0x30];
    u8 low : 4;
    u8 high : 4;
    u8 unknown_32[2];
} Record08044038;

typedef struct {
    u8 unknown_00[0x7B8];
    Record08044038 records[6];
} State08044038;

extern State08044038 *g_state_03002810;

void func_08044038(void)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        if (g_state_03002810->records[i].active) {
            g_state_03002810->records[i].pending = 0;
            g_state_03002810->records[i].low = 0;
            g_state_03002810->records[i].high = 1;
        }
    }
}
