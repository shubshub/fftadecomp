#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 active;
    u8 peer;
} Link;

typedef struct {
    Link links[4];
    u8 unknown_10[4];
} LinkRecord;

typedef struct {
    u8 unknown_00[0x67c];
    LinkRecord *records;
} MenuContext;

extern MenuContext *g_state_03002810;

/* Complete target: [0x080450DC, 0x0804516C), 144 bytes. */
u8 func_080450DC(u8 first, u8 second)
{
    if (first == second)
        return 1;
    if (g_state_03002810->records[first].links[0].active &&
        g_state_03002810->records[first].links[0].peer == second)
        return 1;
    if (g_state_03002810->records[first].links[1].active &&
        g_state_03002810->records[first].links[1].peer == second)
        return 1;
    if (g_state_03002810->records[first].links[2].active &&
        g_state_03002810->records[first].links[2].peer == second)
        return 1;
    if (g_state_03002810->records[first].links[3].active &&
        g_state_03002810->records[first].links[3].peer == second)
        return 1;
    return 0;
}
