#include "ffta.h"
#include "control_flags.h"
/* Target: 0x080F9168..0x080F93E0 (632 bytes). */
typedef struct Descriptor { u16 phase, unknown_2; void *data; u32 unknown_8[3]; u16 value; u16 unknown_16; u32 unknown_18; } Descriptor;
typedef struct State { s16 x,y; u8 mode,ready,active; s8 count; u8 delay,unknown_9; u16 index; void *window; void *items[4]; void *object; void *resources[2]; void *animation; void *data; void *loader; void *transition; void *scene; void *effect; } State;
extern u8 data_0839C3E0[],data_0839C43C[],data_088F58BC[],data_08949AFC[],data_08949CB8[],data_0894ABF0[],data_0894D690[],data_0839C444[];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080DD494(void *);
extern void *func_080DDF68(void *,void **,int,int,u8 *,void *,int,int,void *);
extern void func_080DBDC8(void *,s16 *,s16 *);
extern void *func_080DBB14(void *,int,int,int,void *);
extern void *func_080DBA5C(void *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D4704(void *,void *);
extern void *func_080D4724(void *,void *,int);
extern void *func_080D3E9C(void *,void *);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void *func_080D4774(void *);
extern int func_080D8858(void *,int);
extern int func_080E0570(void **,int);
extern void *func_080DD4A4(void *,u8);
extern int func_080F9094(void *,Descriptor *,void *);
extern void *func_08005B6C(void *callback,int size,Descriptor *descriptor,void *owner);
extern int func_080DE1F0(void *);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(int);
extern int func_080D48DC(void **,int);
int func_080F9168(void *owner,Descriptor *desc,State *s)
{
 Descriptor child;
 switch(desc->phase) {
 case 0: {
 int flags;
 s->mode=desc->unknown_16;
 s->data=desc->data;
 flags=4;
 if(s->mode) flags=0;
 s->loader=func_080E03F8(s->data,data_0839C3E0,flags,0,0,owner);
 break;
 }
 case 1: func_080D38B4(); break;
 case 0x100:
 s->loader=func_080E05DC(s->loader);
 if(!s->loader) {
 if(s->mode) { s->count=func_080DD494(s->data); s->delay=1; desc->phase=0x104; }
 else {
 s->scene=func_080DDF68(s->data,&s->object,0x98,2,&s->ready,data_0839C43C,0,0,owner);
 func_080DBDC8(s->object,&s->x,&s->y);
 desc->phase++;
 }
 } break;
 case 0x101:
 if(s->ready) { s->transition=func_080DBB14(s->object,8,12,0,owner); desc->phase++; } break;
 case 0x102:
 s->transition=func_080DBA5C(s->transition);
 if(!s->transition && s->active) {
 func_080D7220(data_088F58BC,0,2,s->x,s->y,0);
 s->resources[0]=func_080D4704(data_08949AFC,owner);
 s->resources[1]=func_080D4704(data_08949CB8,owner);
 s->animation=func_080D4724(data_0894ABF0,owner,20);
 s->window=func_080D3E9C(data_0894D690,owner);
 s->effect=func_080DFD8C(data_0839C444,1,4,0,owner);
 s->index=60; desc->phase++;
 } break;
 case 0x103:
 if(--s->index==0) {
 s->animation=func_080D4774(s->animation);
 if(!s->animation) {
 s->count=func_080D8858(s->data,0);
 if(s->count<=0) desc->phase=0x105;
 else {s->delay=1;desc->phase++;}
 }
 } break;
 case 0x104:
 func_080E0570(s->items,4);
 if(--s->delay==0) {
 child.value=s->index;
 child.data=func_080DD4A4(s->data,(u8)s->index);
 s->items[s->index]=func_08005B6C(func_080F9094,32,&child,owner);
 s->delay=30;
 s->index++;
 if(s->index==s->count) desc->phase++;
 } break;
 case 0x105:
 if((u8)func_080DE1F0(s->object)) {
 s->window=func_080D3F08(s->window);
 if(!s->window) {
 g_control_flags_03000940.display &= ~func_080035A8(2);
 if((u8)func_080D48DC(s->resources,2) && (u8)func_080E0570(s->items,4)) desc->phase=2;
 }
 } break;
 }
 return 0;
}
