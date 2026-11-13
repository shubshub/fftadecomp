#include "ffta.h"
extern u16 g_control_flags_03000940;
/* Target: 0x0810781C..0x08107AA0 (644 bytes). */
typedef struct Descriptor { u16 phase, unknown_2; u32 argument; void *data; u32 flags; u32 unknown_10; u16 mode, unknown_16; u32 unknown_18; } Descriptor;
typedef struct State { u16 unknown_0; s16 x,y; u8 ready,unknown_7,status,mode,unknown_a,option; u32 unknown_c,position,actor,unknown_18,effect,sprite,transition,loader,task,resource,portrait,text,animation; } State;
extern u8 data_083A0C94[],data_083A0D08[],data_083A0CF0[],data_083A0CC4[],data_088EEB54[],data_0894D844[],data_083A0CF4[],data_083A0D28[];
extern u32 data_083A0CE8[];
extern u32 func_080E03F8(u32, const void *, u32, u32, u32, u32);
extern u32 func_080E05DC(u32);
extern u32 func_080DFD8C(const void *, u32, u32, u32, u32);
extern u32 func_080DDF68(u32, void *, u32, u32, void *, u32, u32, u32, u32);
typedef void (*Callback)(void);
extern u32 func_08005B6C(Callback callback, u32, Descriptor *, u32);
extern u32 func_080DD4A4(u32,u32);
extern u32 func_080DD748(u32,s16 *,s16 *,u32);
extern u32 func_080D6098(s32,s32,u32,u32,u32,void *,const void *,u32);
extern u32 func_080D4B64(u32,const void *,u32,u32);
extern u32 func_080035A8(u32 index);
extern u32 func_080D3E9C(const void *,u32);
extern u32 func_080DCFE4(u32 actor, const void *data, u32 a, u32 b, u32 c, u32 owner, u32 d);
extern u32 func_080D3F08(u32);
extern u32 func_080D4D2C(u32,u32);
extern u32 func_080E051C(u32);
extern u32 func_080D6134(u32);
extern u32 func_080DBA5C(u32);
extern u8 func_080D3B54(u32);
extern u8 func_080D8858(u32,u32);
extern u8 func_080DD73C(void);
extern void func_080D38B4(void);
extern void func_080D49FC(u32,u32,u32,s32,s32);
extern void func_081074D8(void);
u32 func_0810781C(u32 owner, Descriptor *event, State *s)
{
 Descriptor d;
 switch(event->phase) {
 case 0: {
  u32 size;
  u16 option=event->unknown_16;
  s->option=option;
  s->resource=event->argument;
  size=4;
  if((u8)option) size=0;
  if(event->flags&2) s->mode=1;
  s->loader=func_080E03F8(s->resource,data_083A0C94,size,0,0,owner);
  break;
 }
 case 1: func_080D38B4(); break;
 case 0x100: {
  u32 size;
  s->loader=func_080E05DC(s->loader);
  if(s->loader) break;
  if(func_080D3B54(s->resource)) { event->phase=2; break; }
  size=0x54;
  if(s->mode) size=0x34;
  else s->animation=func_080DFD8C(data_083A0D08,3,4,0,owner);
  s->portrait=func_080DDF68(s->resource,&s->unknown_c,size,data_083A0CF0[s->mode],&s->ready,data_083A0CE8[s->mode],0,0,owner);
  d.mode=s->mode;
  d.argument=s->resource;
  d.data=&s->status;
  s->task=func_08005B6C(func_081074D8,0x19c,&d,owner);
  event->phase++;
  break;
 }
 case 0x101:
  if(s->ready && s->status==1) { s->status=2; event->phase++; }
  break;
 case 0x102:
  if(s->status!=3) break;
  if(!func_080D8858(s->resource,0)) { event->phase=0x103; break; }
  s->actor=func_080DD4A4(s->resource,0);
  s->position=func_080DD748(s->actor,&s->x,&s->y,0);
  if(func_080DD73C()) s->y-=8;
  s->effect=func_080D6098(s->x,s->y,0,1,1,&s->unknown_18,data_083A0CC4,owner);
  func_080D49FC(0,2,0,s->x,s->y);
  s->sprite=func_080D4B64(0,data_088EEB54,0x3c4,6);
  { u32 mask=func_080035A8(2); u32 flags=g_control_flags_03000940; flags |=mask; g_control_flags_03000940=flags; }
  s->transition=func_080D3E9C(data_0894D844,owner);
  s->text=func_080DCFE4(s->actor,data_083A0CF4,12,90,10,owner,90);
  s->animation=func_080DFD8C(data_083A0D28,1,4,0,owner);
  event->phase++;
  break;
 case 0x103:
  s->transition=func_080D3F08(s->transition);
  if(s->transition) break;
  s->sprite=func_080D4D2C(s->sprite,0);
  if(s->sprite) break;
  { u32 mask=func_080035A8(2); g_control_flags_03000940 &=~mask; }
  s->task=func_080E051C(s->task);
  if(s->task) break;
  s->effect=func_080D6134(s->effect);
  if(s->effect) break;
  s->text=func_080DBA5C(s->text);
  if(s->text) break;
  event->phase=2;
  break;
 }
 return 0;
}
