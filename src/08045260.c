#include "ffta.h"

// func_08045260: 0x08045260-0x08045390 (304 bytes, 137 instructions)

typedef struct {
    s16 x;
    s16 y;
} Offset;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} Node;

typedef struct {
    u8 unknown_00[3];
    u8 from;
    u8 to;
    u8 unknown_05[2];
    u8 visits;
    u8 step;
    u8 unknown_09[0x21];
    s16 px;
    s16 py;
    u8 unknown_2E[3];
    u8 heading : 4;
    u8 unknown_31_4 : 4;
} Walker;

typedef struct {
    u8 unknown_00[0x67C];
    Node *nodes;
    u8 unknown_680[0x7B8 - 0x680];
    Walker walkers[1];
} WalkState;

extern WalkState *g_state_03002810;
extern u8 func_0804BB10(u8 a, u8 b);
extern u8 func_0804BDB0(u8 a, u8 b);
extern u8 func_0804BDC4(u8 a, u8 b);
extern Offset func_0804BD4C(u8 a, u8 b, u8 index);
extern u8 func_08044D90(u8 a, u8 b, u8 start);
extern void func_08141570(s32 player_id, u16 song_id);

u8 func_08045260(u8 index)
{
    Walker *w = &g_state_03002810->walkers[index];
    Offset off;
    u8 dir;
    u8 dist;
    u8 step;

    if (w->step == 0xFF)
        return 1;
    dir = func_0804BB10(w->from, w->to) - 1;
    dist = func_0804BDB0(w->from, w->to);
    off = func_0804BD4C(dist, dir, w->step);
    if (off.x == 0 && off.y == 0) {
        w->visits++;
        w->step = 0xFF;
        w->from = w->to;
        w->px = g_state_03002810->nodes[w->from].x << 3;
        w->py = g_state_03002810->nodes[w->from].y << 3;
        if (index == 0)
            func_08141570(1, 0x72);
        return 1;
    }
    step = w->step;
    if (step % 5 == 0)
        w->heading = func_08044D90(dist, dir, step);
    {
        u8 m = func_0804BDC4(w->from, w->to);
        w->px = (s8)off.x + (g_state_03002810->nodes[m].x << 3);
        w->py = (s8)off.y + (g_state_03002810->nodes[m].y << 3);
    }
    w->step++;
    return 0;
}
