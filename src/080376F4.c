#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} PositionRecord;

typedef struct {
    u8 unknown_00[3];
    u8 slot;
    u8 unknown_04[0x26];
    u16 x;
    u16 y;
    u8 unknown_2E[3];
    u8 state : 4;
    u8 unknown_31_high : 4;
    u8 unknown_32[2];
} MenuEntry;

typedef struct {
    u8 unknown_000[0x67C];
    PositionRecord *records;
    u8 unknown_680[0x138];
    MenuEntry entries[8];
} MenuContext;

extern MenuContext *g_state_03002810;

/* Complete target: [0x080376F4, 0x0803776C), 120 bytes, 49 instructions. */
void func_080376F4(u8 index, u8 state)
{
    g_state_03002810->entries[index].x =
        g_state_03002810->records[g_state_03002810->entries[index].slot].x * 8;
    g_state_03002810->entries[index].y =
        g_state_03002810->records[g_state_03002810->entries[index].slot].y * 8;
    g_state_03002810->entries[index].state = state;
}
