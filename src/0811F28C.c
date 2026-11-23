// Target span [0x0811F28C, 0x0811F5DE): 850 bytes.
// Target: f0b5474680b481b0061c0b1c151c2988802000020840002800d093e11988012950d0
//
// An effect task that redraws a shape centred on the screen (120, 80) into
// the two window tasks of event->pair at every step (phase 0x100), with a
// full brightness increase (BLDCNT 0xBF, BLDY 16): an ellipse for modes 0
// and 1, func_080DAA10's four-sided shape for modes 2 and 3 and
// func_080DAAC4's for mode 4.  Its sizes and angle follow three
// interpolations over count - 1 steps, from event->source.  func_0811F5E0
// starts it (0x0811F8B4).
#include "control_flags.h"

typedef struct { s16 current, remaining, error, step, period, distance; } InterpolationState;
typedef struct { void *top, *bottom; } Pair;
typedef struct { s16 x0, y0, x1, y1, x2, y2; u16 count; } Source;
typedef struct { u16 state; u16 unknown_2; Source *source; Pair *pair; u8 unknown_c[8]; u16 unknown_14, unknown_16; } Event;
typedef struct {
    u16 state;
    u16 counter;
    u8 unknown_4[4];
    u8 mode;
    u8 flag;
    u8 unknown_a[2];
    InterpolationState first;
    InterpolationState second;
    InterpolationState third;
    void *task;
    Pair *pair;
} State;

extern const u8 data_0894DEE8[];
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void func_080D4020(void);
extern void *func_080D3EC0(const void *, u16, void *);
extern void func_080DADFC(void *);
extern s16 func_08007A60(u8);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void func_080DAA10(void *, u16, u16, u16, u16);
extern void func_080DAAC4(void *, s16, s16, u16, u8);

int func_0811F28C(void *owner, Event *event, State *s)
{
    if (!(s->state & 0x8000)) {
        switch (event->state) {
        case 0: {
            Source *src;
            s->mode = event->unknown_14;
            s->flag = event->unknown_16;
            src = event->source;
            s->pair = event->pair;
            func_080E0608(&s->first, src->x0, src->y0, src->count - 1);
            func_080E0608(&s->second, src->x1, src->y1, src->count - 1);
            func_080E0608(&s->third, src->x2, src->y2, src->count - 1);
            g_control_flags_03000940.bldcnt_lo = 0xbf;
            g_control_flags_03000940.bldy_lo = 0x10;
            if (s->flag == 0)
                s->task = func_080D3EC0(data_0894DEE8, src->count - 11, owner);
            s->counter = src->count - 1;
            break;
        }
        case 1:
            func_080D4020();
            break;
        case 0x100: {
            func_080DADFC(s->pair->top);
            func_080DADFC(s->pair->bottom);
            switch (s->mode) {
            case 0: {
                s16 a, b, c, d;
                a = s->first.current;
                b = (s16)(a * func_08007A60(s->third.current)) >> 8;
                if (b < 0) b = -b;
                c = s->second.current;
                d = (s16)(c * func_08007A60(s->third.current)) >> 8;
                if (d < 0) d = -d;
                func_080DAC80(s->pair->top, 0x78, 0x50, a, b);
                func_080DAC80(s->pair->bottom, 0x78, 0x50, c, d);
                break;
            }
            case 1: {
                s16 a, b, c, d;
                a = s->first.current;
                b = (s16)(a * func_08007A60(s->third.current)) >> 8;
                if (b < 0) b = -b;
                c = s->second.current;
                d = (s16)(c * func_08007A60(s->third.current)) >> 8;
                if (d < 0) d = -d;
                func_080DAC80(s->pair->top, 0x78, 0x50, b, a);
                func_080DAC80(s->pair->bottom, 0x78, 0x50, d, c);
                break;
            }
            case 2: {
                s16 a, b, c, d;
                a = s->first.current;
                b = (s16)(a * func_08007A60(s->third.current)) >> 8;
                if (b < 0) b = -b;
                c = s->second.current;
                d = (s16)(c * func_08007A60(s->third.current)) >> 8;
                if (d < 0) d = -d;
                if (d >= b) d = 0;
                func_080DAA10(s->pair->top, 0x78, 0x50, a, b);
                func_080DAA10(s->pair->bottom, 0x78, 0x50, c, d);
                break;
            }
            case 3: {
                s16 a, b, c, d;
                a = s->first.current;
                b = (s16)(a * func_08007A60(s->third.current)) >> 8;
                if (b < 0) b = -b;
                c = s->second.current;
                d = (s16)(c * func_08007A60(s->third.current)) >> 8;
                if (d < 0) d = -d;
                if (d >= b) d = 0;
                func_080DAA10(s->pair->top, 0x78, 0x50, b, a);
                func_080DAA10(s->pair->bottom, 0x78, 0x50, d, c);
                break;
            }
            case 4:
                func_080DAAC4(s->pair->top, 0x78, 0x50, s->first.current, s->third.current);
                func_080DAAC4(s->pair->bottom, 0x78, 0x50, s->second.current, s->third.current);
                break;
            }
            func_080E064C(&s->first);
            func_080E064C(&s->second);
            func_080E064C(&s->third);
            s->counter--;
            break;
        }
        }
    }
    return 0;
}
