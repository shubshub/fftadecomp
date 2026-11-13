#include "control_flags.h"
/* Target: 0x080EA4A0..0x080EA6F2 (594 bytes). */
typedef struct { u16 state; u16 unknown_2; int value; u8 unknown_8[14]; u16 mode; } Event;
typedef struct { int object; u8 mode; u8 unknown_5[3]; u16 timer; u16 unknown_a; int value; int animation; u8 parameters[32]; int first; int second; int third; int pending; int follow; int effect; int fade; } State;
extern char data_08398988[], data_088F46FC[], data_083989B8[], data_0894D69C[], data_08948DA8[], data_08398A78[], data_08398A90[];
extern int func_080EA3E8(void);
extern int func_080E03F8(int a0,int a1,int a2,int a3,int a4,int a5);
extern int func_080E05DC(int a0);
extern int func_080DFD68(int a0,int a1,int a2);
extern int func_080DFED8(int a0);
extern int func_080D6098(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7);
extern int func_080D3E9C(int a0,int a1);
extern int func_080D4704(int a0,int a1);
extern int func_080D979C(int a0,int a1,int a2,int a3,int a4);
extern int func_08005B6C(int a0,int a1,int a2,int a3);
extern int func_080DFD8C(int a0,int a1,int a2,int a3,int a4);
extern int func_080D6134(int a0);
extern int func_080D3F08(int a0);
extern int func_080D4774(int a0);
extern int func_080035A8(int a0);
extern int func_080D8858(int a0,int a1);
extern int func_080EDB98(int a0,int a1,int a2);
extern int func_080EDBDC(int a0);
extern void func_080D38B4(void);
extern void func_080D7220(int a0,int a1,int a2,int a3,int a4,int a5);
extern void func_080D984C(int a0,int a1,int a2,int a3);
extern void func_080EDB80(int a0);
extern void func_080D9B38(int a0);
extern void func_08005B58(int object);
extern void func_080D9B58(int a0);
int func_080EA4A0(int owner, Event *event, State *s)
{
 int buffer[7]; int done;
 switch(event->state) {
 case 0:
 s->mode=event->mode; s->value=event->value;
 if(!s->mode) s->pending=func_080E03F8(s->value,data_08398988,4,4,0,owner);
 break;
 case 1: func_080D38B4(); break;
 case 0x100:
 if(s->mode) { s->pending=func_080E05DC(s->pending); if(!s->pending) event->state=0x104; }
 else { s->fade=func_080DFD68(1,30,owner); event->state++; }
 break;
 case 0x101:
 s->pending=func_080E05DC(s->pending);
 if(s->pending) break;
 s->fade=func_080DFED8(s->fade);
 if(s->fade) break;
 func_080D7220(data_088F46FC,0,2,0,0,0);
 s->animation=func_080D6098(0,0,0,0,8,s->parameters,data_083989B8,owner);
 s->first=func_080D3E9C(data_0894D69C,owner);
 s->second=func_080D4704(data_08948DA8,owner);
 s->third=func_080D979C(1,2,0,data_08398A78,owner);
 func_080D984C(s->third,0,4,155);
 func_080D984C(s->third,1,64,111);
 s->object=func_08005B6C(func_080EA3E8,8,buffer,owner);
 s->effect=func_080DFD8C(data_08398A90,10,4,0,owner);
 s->timer=301; event->state++; break;
 case 0x102:
 done=1;
 if(s->timer) { if(!--s->timer) { s->fade=func_080DFD68(0,30,owner); func_080EDB80(s->value); } }
 s->animation=func_080D6134(s->animation); if(s->animation) done=0;
 s->first=func_080D3F08(s->first); if(s->first) done=0;
 s->second=func_080D4774(s->second); if(s->second) done=0;
 if(done) { func_080D9B38(s->third); g_control_flags_03000940.display &= ~func_080035A8(2); func_08005B58(s->object); s->object=0; event->state++; }
 break;
 case 0x103:
 s->fade=func_080DFED8(s->fade);
 if(!s->fade) { func_080D9B58(s->third); if((u8)func_080D8858(s->value,0)) event->state++; else event->state=2; }
 break;
 case 0x104: s->follow=func_080EDB98(s->value,0,owner); event->state++; break;
 case 0x105: s->follow=func_080EDBDC(s->follow); if(!s->follow) event->state=2; break;
 }
 return 0;
}
