// Target: complete [0x0811B888, 0x0811BB06), 638 bytes, 269 instructions,
// including three literal pools.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
} Event;

typedef struct {
    s16 value;
    u16 unknown_02;
    int unknown_04;
    int unknown_08;
} Motion;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *timeline;
    void *bar[2];
    void *startup;
    Motion third;
    Motion first;
    Motion second;
    void *record_task;
} State;

extern u16 data_03003860[][16];
extern const u8 data_083A6B04[];
extern const u8 data_083A6B1C[];
extern const u8 data_088F46CC[];
extern const u8 data_0894DDAC[];

extern void *func_080D7A70(const void *, u8, void *);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080DAB84(int, int, int, void *);
extern void func_080D9BA8(void *, int);
extern void *func_080D9B64(void *);
extern void func_080E0608(Motion *, s16, s16, s16);
extern void func_080E064C(Motion *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void func_0801C960(s16, s16, s16 *, s16 *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u16 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void func_080DBED4(u32, u32, u32, void *);

u32 func_0811B888(void *owner, Event *event, State *s)
{
    void **bar;

    switch (event->phase) {
    case 0:
        s->startup = func_080D7A70(data_083A6B04, 2, owner);
        data_03003860[6][1] = 0x396D;
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        s->startup = func_080D7ABC(s->startup);
        if (s->startup != 0)
            break;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        s->timeline = func_080D3E9C(data_0894DDAC, owner);
        bar = s->bar;
        bar[0] = func_080DAB84(1, 0, 0, owner);
        bar[1] = func_080DAB84(0, 0, 0, owner);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xa0;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 0xa0;
        g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.winin_hi = 0x3f;
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.display |= 0x6000;
        func_080D9BA8(bar[0], 1);
        func_080D9BA8(bar[1], 1);
        func_080E0608(&s->first, 0, 0x78, 0x28);
        func_080E0608(&s->second, 0, 0x78, 0x20);
        s->timer = 8;
        func_080E0608(&s->third, 0, 5, 0x20);
        func_0801C960(0xd0, 0x108, &s->x, &s->y);
        s->record_task = func_080DFD8C(data_083A6B1C, 1, 4, 0, owner);
        event->phase++;
        break;
    case 0x101:
        func_080E064C(&s->first);
        func_080DAC80(s->bar[0], s->x, s->y, s->first.value,
                      (u16)(s->first.value >> 1));
        if (s->timer) {
            s->timer--;
        } else {
            func_080E064C(&s->second);
            func_080E064C(&s->third);
            func_080DAC80(s->bar[1], s->x, (s16)(s->y - s->third.value),
                          s->second.value, (u16)(s->second.value >> 1));
        }
        s->timeline = func_080D3F08(s->timeline);
        if (s->timeline != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= 0x9fff;
        g_control_flags_03000940.bldcnt_lo = 0;
        func_080DBED4(0, 0, 0, 0);
        event->phase++;
        break;
    case 0x102:
        s->bar[0] = func_080D9B64(s->bar[0]);
        if (s->bar[0] != 0)
            break;
        s->bar[1] = func_080D9B64(s->bar[1]);
        if (s->bar[1] != 0)
            break;
        event->phase = 2;
        break;
    }
    return 0;
}
