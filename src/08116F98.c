/* Target bytes: f0b54f464646c0b482b081468846161c09888020400081421bd0814202dc00290cd0fee00448814200d193e00130814200d1dbe0f5e000000101000041464868b060b11c321dc4f7f3feb0880838b080e7e00320ecf6f0fa3a4f3f24221c8243101c3a1c4232117800251070391c433108783f2008700320ecf6defa8443381c443001780470391c3b3108780d70013908780d70053108780d700139ff200870013908780d70381c3c3001780570391c413108780d70013908780120404208703988c023db01181c08433880301c1430402100221e23c9f7cbfa301c2030302100221e23c9f7c4fa0120002100224b46c3f77cfdf0620020002100224b46c3f775fd3063f06a0121c2f782fd306b0121c2f77efd0c4800950195012103220023c0f7b2f809484946bcf7ecfef0600821ff22bcf75bff06484946bdf717fb30614be0000040090003cc468f089cd6940814c59408351c1435281cc9f7abfa371c2037381cc9f7a6faf06ac3f77bfe306bc3f778fef06a0222b15eb288023212041214b38a1c0464142404240c0094c3f7abfd306b0223f15e0423f25e338c1c0464142404240c0094c3f79efd281cc9f7a3fa0006002834d0381cc9f79dfa000600282ed0074c21880748084020800320ecf61efa21888143218041460888013008801ee040090003ff9f0000f06ac2f7edfcf062002814d1306bc2f7e7fc306300280ed1f068bcf7b3fef060002808d13069bdf7e3fa3061002802d1022042461080002002b018bc9846a146f0bc02bc0847 */
#include "control_flags.h"
typedef struct { s16 value; u16 unknown_2; int unknown_4; int unknown_8; } Motion;
typedef struct { u16 state; u16 unknown_2; void *resource; } Event;
typedef struct { u16 unknown_0; s16 x, y; u16 unknown_6; void *resource; void *a, *b; Motion first, second; void *top, *bottom; } State;
extern u8 data_088F46CC[], data_0894D69C[], data_0894C514[];
extern void func_080DBDC8(void *, s16 *, s16 *);
extern int func_080035D0(int);
extern int func_080035A8(int);
extern void func_080E0608(Motion *, s16, s16, s16);
extern void func_080E064C(Motion *);
extern u8 func_080E0690(Motion *);
extern void *func_080DAB84(int,int,int,void *);
extern void func_080D9BA8(void *,int);
extern void func_080D7220(const void *,u8,u8,s16,s16,u16);
extern void *func_080D3E9C(const void *,void *);
extern void func_080D3F84(void *,int,int);
extern void *func_080D4704(const void *,void *);
extern void func_080DADFC(void *);
extern void func_080DAC80(void *,s16,s16,u16,u16);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
int func_08116F98(void *owner, Event *event, State *s)
{
    switch (event->state) {
    case 0:
        s->resource = event->resource;
        func_080DBDC8(s->resource, &s->x, &s->y);
        s->y -= 8;
        break;
    case 0x100:
        g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(3);
        g_control_flags_03000940.winin_hi = 0x3f;
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(3);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = -1;
        g_control_flags_03000940.display |= 0x6000;
        func_080E0608(&s->first,64,0,30);
        func_080E0608(&s->second,48,0,30);
        s->top = func_080DAB84(1,0,0,owner);
        s->bottom = func_080DAB84(0,0,0,owner);
        func_080D9BA8(s->top,1);
        func_080D9BA8(s->bottom,1);
        func_080D7220(data_088F46CC,1,3,0,0,0);
        s->a = func_080D3E9C(data_0894D69C,owner);
        func_080D3F84(s->a,8,255);
        s->b = func_080D4704(data_0894C514,owner);
        event->state++;
        break;
    case 0x101:
        func_080E064C(&s->first);
        func_080E064C(&s->second);
        func_080DADFC(s->top);
        func_080DADFC(s->bottom);
        func_080DAC80(s->top,s->x,(s16)(s->y+2),s->first.value,(u16)(s->first.value>>1));
        func_080DAC80(s->bottom,s->x,s->y,s->second.value,(u16)(s->second.value>>1));
        if (func_080E0690(&s->first) && func_080E0690(&s->second)) {
            g_control_flags_03000940.display &= 0x9fff;
            g_control_flags_03000940.display &= ~func_080035A8(3);
            event->state++;
        }
        break;
    case 0x102:
        if (!(s->top = func_080D9B64(s->top)) &&
            !(s->bottom = func_080D9B64(s->bottom)) &&
            !(s->a = func_080D3F08(s->a)) &&
            !(s->b = func_080D4774(s->b))) event->state = 2;
        break;
    }
    return 0;
}
