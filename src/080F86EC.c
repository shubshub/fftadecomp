#include "ffta.h"
#include "control_flags.h"
/* Target: 0x080F86EC..0x080F897C (656 bytes). */
struct State { s16 x,y; u8 unknown_04,mode,ready,unknown_07; s8 count; u8 delay; u16 index; u32 unknown_0c[3]; u32 effect,transition,children[4],object,first,second,resource,loading,dialog,overlay; };
struct Event { u16 state,unknown_02; u32 resource; u8 unknown_08[14]; u16 mode; };
struct Params { u32 unknown_00,resource,unknown_08[3]; u16 index; u16 unknown_16; u32 unknown_18; };
extern u8 data_0839C030[],data_0839C104[],data_0839C078[],data_0839C108[],data_088F58BC[],data_0894A130[],data_0894ABF0[],data_0894D92C[];
extern int func_080F8608(void);
extern int func_080E03F8(u32,void *,int,int,int,void *);
extern int func_080D38B4(void);
extern int func_080E05DC(u32);
extern int func_080DD494(u32);
extern int func_080DDF68(u32,void *,int,int,void *,void *,int,int,void *);
extern int func_080DBDC8(u32,void *,void *);
extern int func_080D6098(int,int,int,int,int,void *,void *,void *);
extern int func_080DBC88(u32);
extern int func_080D6194(u32,int);
extern int func_080DFD8C(void *,int,int,int,void *);
extern int func_080D7220(void *,int,int,int,int,int);
extern int func_080D4704(void *,void *);
extern int func_080D3E9C(void *,void *);
extern int func_080DE1F0(u32);
extern int func_080D8858(u32,int);
extern int func_080E0570(void *,int);
extern int func_080DD4A4(u32,int);
typedef int Callback(void);
extern int func_08005B6C(Callback *,int,void *,void *);
extern int func_080D6134(u32);
extern int func_080D3F08(u32);
extern int func_080035A8(int);
extern int func_080D4774(u32);
int func_080F86EC(void *owner,struct Event *event,struct State *s)
{
 struct Params params;
 switch(event->state) {
 case 0: {
 int flags;
 s->mode=event->mode;
 s->resource=event->resource;
 flags=6;
 if(s->mode) flags=0;
 s->loading=func_080E03F8(s->resource,data_0839C030,flags,0,0,owner);
 break;
 }
 case 1: func_080D38B4(); break;
 case 0x100:
 s->loading=func_080E05DC(s->loading);
 if(!s->loading) {
 if(s->mode) { s->count=func_080DD494(s->resource); s->delay=1; event->state=0x104; }
 else {
 s->dialog=func_080DDF68(s->resource,&s->object,0x94,1,&s->ready,data_0839C104,0,0,owner);
 func_080DBDC8(s->object,s,&s->y);
 event->state++;
 }
 } break;
 case 0x101:
 if(s->ready) {
 s->effect=func_080D6098(s->x,s->y,0,1,3,s->unknown_0c,data_0839C078,owner);
 if((s8)func_080DBC88(s->object)>1) func_080D6194(s->effect,1);
 s->overlay=func_080DFD8C(data_0839C108,2,4,0,owner);
 s->index=21;
 event->state++;
 } break;
 case 0x102:
 if(--s->index==0) {
 func_080D7220(data_088F58BC,0,2,s->x,s->y,0);
 s->first=func_080D4704(data_0894A130,owner);
 s->second=func_080D4704(data_0894ABF0,owner);
 s->transition=func_080D3E9C(data_0894D92C,owner);
 event->state++;
 } break;
 case 0x103:
 if((u8)func_080DE1F0(s->object)) {
 s->count=func_080D8858(s->resource,0);
 if(s->count<=0) event->state=0x105;
 else {s->delay=1;event->state++;}
 } break;
 case 0x104:
 func_080E0570(s->children,4);
 if(--s->delay==0) {
 params.index=s->index;
 params.resource=func_080DD4A4(s->resource,(u8)s->index);
 s->children[s->index]=func_08005B6C(func_080F8608,0x24,&params,owner);
 s->delay=30;
 s->index++;
 if(s->index==s->count) event->state++;
 } break;
 case 0x105:
 s->effect=func_080D6134(s->effect);
 if(s->effect) break;
 s->transition=func_080D3F08(s->transition);
 if(s->transition) break;
 g_control_flags_03000940.display &= ~func_080035A8(2);
 s->first=func_080D4774(s->first);
 if(s->first) break;
 s->second=func_080D4774(s->second);
 if(s->second) break;
 if((u8)func_080E0570(s->children,4)) event->state=2;
 break;
 }
 return 0;
}
