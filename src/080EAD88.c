#include "ffta.h"
#include "control_flags.h"
/* Target: 0x080EAD88..0x080EAFC6, 574 bytes. */
struct Descriptor { u32 words[7]; };
struct Event { u16 state, unknown_2; u32 resource; u32 unknown_8[3]; u16 unknown_20, mode; };
struct State { u16 timer; u8 mode, unknown_3; u32 a,b,c,d,e,resource,f,g,h,i; };
extern u8 data_08398C30[], data_08398DB0[], data_088F4D34[], data_08948FF4[], data_0894D69C[], data_08398D88[];
extern void func_080D38B4(void);
extern u32 func_080E03F8(u32,void*,int,int,int,void*);
extern u32 func_080E05DC(u32);
extern u32 func_080DFED8(u32);
extern u32 func_080DFD68(int,int,void*);
extern u32 func_080DFD8C(void*,int,int,int,void*);
extern u32 func_08005B6C(void*,int,struct Descriptor*,void*);
extern void func_080D7220(void*,int,int,int,int,int);
extern u32 func_080D4704(void*,void*);
extern u32 func_080D3E9C(void*,void*);
extern u32 func_080D98D4(int,int,int,int,void*,void*);
extern u32 func_080035A8(int);
extern void func_08005B58(u32);
extern void func_080EDB80(u32);
extern u32 func_080D3F08(u32);
extern u32 func_080D4774(u32);
extern void func_080D9B38(u32);
extern void func_080D9B58(u32);
extern u8 func_080D8858(u32,int);
extern u32 func_080EDB98(u32,int,void*);
extern u32 func_080EDBDC(u32);
extern void func_080EAB34(void);
extern void func_080EABE0(void);
int func_080EAD88(void *owner,struct Event *event,struct State *s)
{
 struct Descriptor descriptor;
 switch(event->state) {
 case 0:
  s->mode=event->mode; s->resource=event->resource;
  if(!s->mode) s->g=func_080E03F8(s->resource,data_08398C30,6,4,0,owner);
  break;
 case 1: func_080D38B4(); break;
 case 256:
  if(s->mode) { s->g=func_080E05DC(s->g); if(!s->g) event->state=261; }
  else { s->i=func_080DFD68(1,30,owner); event->state++; }
  break;
 case 257:
  s->g=func_080E05DC(s->g); if(s->g) break;
  s->i=func_080DFED8(s->i); if(s->i) break;
  s->h=func_080DFD8C(data_08398DB0,2,4,0,owner);
  s->a=func_08005B6C((void*)func_080EAB34,20,&descriptor,owner);
  s->b=func_08005B6C((void*)func_080EABE0,728,&descriptor,owner);
  s->timer=120; event->state++; break;
 case 258:
  if(--s->timer) break;
  func_080D7220(data_088F4D34,0,2,0,0,0);
  s->d=func_080D4704(data_08948FF4,owner);
  s->c=func_080D3E9C(data_0894D69C,owner);
  s->e=func_080D98D4(2,0,0,0,data_08398D88,owner);
  s->timer=240; event->state++; break;
 case 259:
  if(s->timer && !--s->timer) {
   g_control_flags_03000940.display &= ~func_080035A8(3);
   func_08005B58(s->a); s->a=0;
   func_08005B58(s->b); s->b=0;
   s->i=func_080DFD68(0,30,owner); func_080EDB80(s->resource);
  }
  s->c=func_080D3F08(s->c); if(s->c) break;
  s->d=func_080D4774(s->d); if(s->d) break;
  func_080D9B38(s->e); event->state++; break;
 case 260:
  s->i=func_080DFED8(s->i); if(s->i) break;
  func_080D9B58(s->e);
  if(func_080D8858(s->resource,0)) event->state++;
  else event->state=2;
  break;
 case 261: s->f=func_080EDB98(s->resource,2,owner); event->state++; break;
 case 262: s->f=func_080EDBDC(s->f); if(!s->f) event->state=2; break;
 }
 return 0;
}
