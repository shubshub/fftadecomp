// Target: complete [0x080F4A70, 0x080F4C6C), 508 bytes, 225 instructions,
// including two literal pools.
#include "control_flags.h"

typedef struct {
    s16 value;
    u16 unknown_02;
    int unknown_04;
    int unknown_08;
} Motion;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *resource;
} Event;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *resource;
    void *script;
    Motion first;
    Motion second;
    void *top;
    void *bottom;
} State;

extern const u8 data_0839B278[];
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080E0608(Motion *, s16, s16, s16);
extern void func_080E064C(Motion *);
extern u8 func_080E0690(Motion *);
extern void *func_080DAB84(int, int, int, void *);
extern void func_080D9BA8(void *, int);
extern void *func_080D3EC0(const void *, u16, void *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);

int func_080F4A70(void *owner, Event *event, State *s)
{
    switch (event->state) {
    case 0:
        s->resource = event->resource;
        func_080DBDC8(s->resource, &s->x, &s->y);
        s->y -= 8;
        break;
    case 0x100:
        g_control_flags_03000940.bldcnt_lo = 0xbf;
        g_control_flags_03000940.bldy_lo = 12;
        g_control_flags_03000940.winin_lo = 0x1f;
        g_control_flags_03000940.winin_hi = 0x3f;
        g_control_flags_03000940.winout_lo = 0x1f;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = -1;
        g_control_flags_03000940.display |= 0x6000;
        func_080E0608(&s->first, 4, 64, 26);
        func_080E0608(&s->second, 4, 64, 20);
        s->timer = 8;
        s->top = func_080DAB84(1, 0, 0, owner);
        s->bottom = func_080DAB84(0, 0, 0, owner);
        func_080D9BA8(s->top, 1);
        func_080D9BA8(s->bottom, 1);
        s->script = func_080D3EC0(data_0839B278, 16, owner);
        event->state++;
        break;
    case 0x101:
        func_080E064C(&s->first);
        func_080DAC80(s->top, s->x, (s16)(s->y + 2), s->first.value,
                      (u16)(s->first.value >> 1));
        if (s->timer) {
            s->timer--;
            break;
        }
        func_080E064C(&s->second);
        func_080DAC80(s->bottom, s->x, s->y, s->second.value,
                      (u16)(s->second.value >> 1));
        if (func_080E0690(&s->first) && func_080E0690(&s->second)) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.display &= 0x9fff;
            event->state++;
        }
        break;
    case 0x102:
        if (!(s->top = func_080D9B64(s->top)) &&
            !(s->bottom = func_080D9B64(s->bottom)) &&
            !(s->script = func_080D3F08(s->script)))
            event->state = 2;
        break;
    }
    return 0;
}
