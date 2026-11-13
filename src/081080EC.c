#include "ffta.h"
#include "control_flags.h"
/* Target: 0x081080EC..0x0810835C (624 bytes). */
typedef struct { u16 phase, unknown_02; void *resource; u32 unknown_08, flags; u8 unknown_10[6]; u16 mode; u32 unknown_18; } Descriptor;
typedef struct { u16 unknown_00; s16 x,y; u8 ready,unknown_07,status,mode,unknown_0a,option; u32 unknown_0c; void *object,*resource; u32 detail[3]; void *position,*effect,*first,*second,*opening,*task,*input,*render,*closing,*auxiliary; } State;
extern u8 data_083A0E04[],data_083A0ECC[],data_083A0EB4[],data_083A0E58[],data_088F469C[],data_0894A0FC[],data_0894AAB0[],data_0894D69C[],data_083A0EB8[],data_083A0EDC[];
extern void *data_083A0EAC[];
typedef struct { u16 phase, unknown_02; void *resource; u32 unknown_08, unknown_0c, unknown_10; u16 mode, unknown_16; u32 unknown_18; } SchedulerDescriptor;
typedef void Callback();
extern void func_08107DA8();
extern void *func_080E03F8(void *, void *, int, int, int, void *);
extern void *func_080E05DC(void *);
extern void *func_080DFD8C(void *, int, int, int, void *);
extern void *func_080DDF68(void *, void *, int, int, void *, void *, int, int, void *);
extern void *func_08005B6C(Callback *, int, SchedulerDescriptor *, void *);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void *func_080D6098(int, int, int, int, int, void *, void *, void *);
extern void *func_080D4704(void *, void *);
extern void *func_080D4724(void *, void *, int);
extern void *func_080D3E9C(void *, void *);
extern void *func_080DCFE4(void *, void *, int, int, int, void *, int);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);
extern void func_080D38B4(void);
extern void func_080D7220(void *, int, int, int, int, int);
extern u8 func_080D3B54(void *);
extern u8 func_080D8858(void *, int);
extern u16 func_080035A8(int);
int func_081080EC(void *owner, Descriptor *d, State *s)
{
    SchedulerDescriptor next;
    int amount;
    switch(d->phase) {
    case 0: {
        int initial_amount;
        u16 mode = d->mode;
        s->option=mode;
        s->input=d->resource;
        initial_amount=7;
        if ((u8)mode) initial_amount=0;
        if(d->flags & 2) s->mode=1;
        s->opening=func_080E03F8(s->input,data_083A0E04,initial_amount,0,0,owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->opening=func_080E05DC(s->opening);
        if(s->opening) break;
        if(func_080D3B54(s->input)) { d->phase=2; break; }
        amount=0x58;
        if(s->mode) amount=0x34;
        else s->auxiliary=func_080DFD8C(data_083A0ECC,1,4,0,owner);
        s->render=func_080DDF68(s->input,&s->unknown_0c,amount,data_083A0EB4[s->mode],&s->ready,data_083A0EAC[s->mode],0,0,owner);
        next.mode=s->mode;
        next.resource=s->input;
        next.unknown_08=(u32)&s->status;
        s->task=func_08005B6C(func_08107DA8,0x19c,&next,owner);
        d->phase++;
        break;
    case 0x101:
        if(s->ready && s->status==1) { s->status=2; d->phase++; }
        break;
    case 0x102:
        if(s->status!=3) break;
        if(!func_080D8858(s->input,0)) {d->phase=0x103;break;}
        s->resource=func_080DD4A4(s->input,0);
        s->object=func_080DD748(s->resource,&s->x,&s->y,0);
        s->position=func_080D6098(s->x,s->y,0,1,3,s->detail,data_083A0E58,owner);
        func_080D7220(data_088F469C,0,2,s->x,(s16)(s->y-4),0);
        s->first=func_080D4704(data_0894A0FC,owner);
        s->second=func_080D4724(data_0894AAB0,owner,10);
        s->effect=func_080D3E9C(data_0894D69C,owner);
        s->closing=func_080DCFE4(s->resource,data_083A0EB8,12,47,12,owner,47);
        s->auxiliary=func_080DFD8C(data_083A0EDC,1,4,0,owner);
        d->phase++;
        break;
    case 0x103:
        s->effect=func_080D3F08(s->effect); if(s->effect) break;
        s->first=func_080D4774(s->first); if(s->first) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        s->second=func_080D4774(s->second); if(s->second) break;
        s->position=func_080D6134(s->position); if(s->position) break;
        s->closing=func_080DBA5C(s->closing); if(s->closing) break;
        d->phase=2;
        break;
    }
    return 0;
}
