#include "ffta.h"
// Target: 0x080F990C..0x080F9B14 (520 bytes).
typedef struct Descriptor { u16 phase, unknown_2; void *data; u32 unknown_8[3]; u16 value; u16 unknown_16; u32 unknown_18; } Descriptor;
typedef struct State { u8 count, index, delay, mode, ready; u8 unknown_5[3]; void *task; void *items[2]; void *object; void *loader; void *data; void *scene; void *effect; } State;
extern u8 data_0839C4E8[], data_0839C544[], data_0839C54C[];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080DD494(void *);
extern void *func_080DDF68(void *,void **,int,int,u8 *,void *,int,int,void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void *func_080E051C(void *);
extern int func_080D8858(void *,int);
extern u8 func_080E0570(void **,int);
extern void *func_080DD4A4(void *,u8);
extern int func_080F9524(void *,Descriptor *,void *);
extern int func_080F9838(void *,Descriptor *,void *);
extern void *func_08005B6C(void *callback,int size,Descriptor *descriptor,void *owner);
extern u8 func_080DE1F0(void *);
int func_080F990C(void *owner,Descriptor *desc,State *s)
{
 Descriptor child;
 Descriptor entry;
 switch(desc->phase) {
 case 0: {
 int flags;
 s->mode=desc->unknown_16;
 s->data=desc->data;
 flags=4;
 if(s->mode) flags=0;
 s->loader=func_080E03F8(s->data,data_0839C4E8,flags,0,0,owner);
 break;
 }
 case 1: func_080D38B4(); break;
 case 0x100:
 s->loader=func_080E05DC(s->loader);
 if(!s->loader) {
 if(s->mode) { s->count=func_080DD494(s->data); s->delay=1; desc->phase=0x104; }
 else {
 s->scene=func_080DDF68(s->data,&s->object,0x8007,2,&s->ready,data_0839C544,3,0,owner);
 desc->phase++;
 }
 } break;
 case 0x101:
 if(s->ready) { func_080D8CD4(s->data); s->index=10; desc->phase++; } break;
 case 0x102:
 if(s->index) { if(--s->index) break; }
 if(func_080D8B4C()) break;
 child.data=s->data;
 s->task=func_08005B6C(func_080F9524,0x34,&child,owner);
 s->effect=func_080DFD8C(data_0839C54C,1,4,0,owner);
 desc->phase++;
 break;
 case 0x103:
 s->task=func_080E051C(s->task);
 if(!s->task) {
 s->count=func_080D8858(s->data,0);
 if(!s->count) desc->phase=0x105;
 else {s->delay=1;desc->phase++;}
 } break;
 case 0x104:
 func_080E0570(s->items,2);
 if(--s->delay==0) {
 u8 slot=s->items[0]!=0;
 entry.value=s->index;
 entry.data=func_080DD4A4(s->data,s->index);
 s->items[slot]=func_08005B6C(func_080F9838,0x20,&entry,owner);
 s->delay=40;
 s->index++;
 if(s->index==s->count) desc->phase++;
 } break;
 case 0x105:
 if(func_080DE1F0(s->object) && func_080E0570(s->items,2)) desc->phase=2;
 break;
 }
 return 0;
}
