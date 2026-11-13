#include "ffta.h"
/* Target: 0x081083EC..0x08108630, 580 bytes. */
typedef struct { u16 phase, unknown_02; void *actor; u32 unknown_08,flags; u8 unknown_10[6]; u16 flag; } Descriptor;
typedef struct {
 s16 x,y; u8 unknown_04,flag,mode,ready,unknown_08,count,timer,unknown_0b; u16 index,unknown_0e;
 void *children[4]; void *output,*timeline,*effect,*other,*actor,*initial,*output_task,*unknown_3c,*unknown_40,*record;
} Payload;
/* Scheduler 08005954 copies a 28-byte descriptor (docs/audio-duration-helpers.md). */
typedef struct {u32 unknown_00; void *actor; u8 unknown_08[12]; u16 index,unknown_16; u32 unknown_18;} Child;
extern const u8 data_083A0EF4[],data_083A0F34[],data_083A0F38[],data_088F5B18[],data_0894DC70[],data_0894BF74[],data_0894848C[],data_083A0F40[];
extern u16 g_control_flags_03000940;
extern u32 func_0810835C();
extern void *func_080E03F8(void *,const void *,u8,u8,u32,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *,u16);
extern void *func_080DDF68(void *,void **,u16,u8,u8 *,const void *,u16,u16,void *);
extern void func_080DBDC8(void *,s16 *,s16 *);
extern void *func_080DFD8C(const void *,u8,u16,u16,void *);
extern void func_080D7220(const void *,u8,u16,s16,s16,u32);
extern void *func_080D3E9C(const void *,void *);
extern void *func_080D4704(const void *,void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern u8 func_080E0570(void **,u32);
extern void *func_080DD4A4(void *,u8);
extern void *func_08005B6C(u32 (*)(),u32,void *,void *);
extern u8 func_080DE1F0(void *);
u32 func_081083EC(void *task,Descriptor *descriptor,Payload *payload)
{
 u8 animation; u16 output_mode; Child child;
 switch(descriptor->phase) {
 case 0:
 payload->flag=descriptor->flag; payload->actor=descriptor->actor;
 animation=2; if(payload->flag) animation=0;
 if(descriptor->flags&2) payload->mode=1;
 payload->initial=func_080E03F8(payload->actor,data_083A0EF4,animation,0,0,task); break;
 case 1:func_080D38B4();break;
 case 0x100:
 payload->initial=func_080E05DC(payload->initial); if(payload->initial) break;
 payload->count=func_080D8858(payload->actor,0); if(!payload->count) {descriptor->phase=2;break;}
 output_mode=92; if(payload->mode) output_mode=148;
 payload->output_task=func_080DDF68(payload->actor,&payload->output,output_mode,1,&payload->ready,data_083A0F34,0,0,task);
 func_080DBDC8(payload->output,&payload->x,&payload->y);
 payload->record=func_080DFD8C(data_083A0F38,1,4,0,task);descriptor->phase++;break;
 case 0x101:
 if(!payload->ready) break;
 func_080D7220(data_088F5B18,0,2,payload->x,(s16)(payload->y-12),0);
 payload->timeline=func_080D3E9C(data_0894DC70,task);
 payload->effect=func_080D4704(data_0894BF74,task);
 payload->other=func_080D4704(data_0894848C,task);
 payload->record=func_080DFD8C(data_083A0F40,1,4,0,task);descriptor->phase++;break;
 case 0x102:
 payload->timeline=func_080D3F08(payload->timeline);if(payload->timeline)break;
 payload->effect=func_080D4774(payload->effect);if(payload->effect)break;
 {u32 mask=func_080035A8(2);u16 flags=g_control_flags_03000940;flags&=~mask;g_control_flags_03000940=flags;}
 payload->other=func_080D4774(payload->other);if(payload->other)break;
 payload->timer=1;descriptor->phase++;break;
 case 0x103:
 func_080E0570(payload->children,4);
 if(--payload->timer)break;
 child.index=payload->index;
 child.actor=func_080DD4A4(payload->actor,(u8)payload->index);
 payload->children[payload->index]=func_08005B6C(func_0810835C,24,&child,task);
 payload->timer=30;
 if(++payload->index==payload->count) descriptor->phase++;
 break;
 case 0x104:if(func_080E0570(payload->children,4))descriptor->phase++;break;
 case 0x105:if(func_080DE1F0(payload->output))descriptor->phase=2;break;
 }
 return 0;
}
