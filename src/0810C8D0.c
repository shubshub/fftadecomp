#include "control_flags.h"
/* Target: 0x0810C8D0..0x0810CB66, 662 bytes. */
typedef struct {u16 state, unknown_2; int resource; int unknown_8; int flags; u16 unknown_10[3]; u16 mode;} CallbackEntry;
typedef struct {s16 x,y; u8 unknown_4,mode,flag,ready,unknown_8; s8 count; u8 timer,unknown_b; u16 index; u8 unknown_e[2]; int unknown_10[4]; int effect,object; void *handles[2]; int visual,other,resource,loading,animation,final;} State;
/* The scheduler copies seven words from this descriptor at 080059F2..080059FC. */
typedef struct {int unknown_0; int resource; int unknown_8[3]; u16 index; u16 unknown_16; u32 unknown_18;} Params;
extern char data_083A252C[],data_083A260C[],data_088F58BC[],data_0894CC30[],data_0894D69C[],data_083A2580[],data_083A2610[];
extern int func_080E03F8(int,void *,int,int,int,int);
extern int func_080E05DC(int);
extern int func_080DD494(int);
extern int func_080DDF68(int,int *,int,int,u8 *,void *,int,int,int);
extern int func_080D4704(void *,int);
extern int func_080D3E9C(void *,int);
extern int func_080D6098(int,int,int,int,int,int *,void *,int);
extern int func_080DBC88(int);
extern int func_080DFD8C(void *,int,int,int,int);
extern int func_080D6134(int);
extern int func_080D4774(int);
extern int func_080D3F08(int);
extern int func_080035A8(int);
extern int func_080D8858(int,int);
extern int func_080D8B4C(void);
extern int func_080E0570(void **,int);
extern int func_080DD4A4(int,int);

extern void *func_08005B6C(void *callback,int,Params *,int);
extern int func_080DE1F0(int);
extern void func_080D38B4(void);
extern void func_080DBDC8(int,s16 *,s16 *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void func_080D6194(int,int);
extern void func_080D8CD4(int);
extern void func_0810C730(void);
int func_0810C8D0(int owner, CallbackEntry *entry, State *s)
{
    Params p;
    int priority;
    u8 position;
    switch(entry->state) {
    case 0:
        s->mode=entry->mode;
        s->resource=entry->resource;
        priority=7;
        if(s->mode) priority=0;
        if(entry->flags & 2) s->flag=1;
        s->loading=func_080E03F8(s->resource,data_083A252C,priority,0,0,owner);
        break;
    case 1: func_080D38B4(); break;
    case 0x100:
        s->loading=func_080E05DC(s->loading);
        if(s->loading) break;
        if(s->mode) {
            s->count=func_080DD494(s->resource);
            s->timer=1;
            entry->state=0x104;
        } else {
            int y=0x58;
            if(s->flag) y=0x3c;
            s->animation=func_080DDF68(s->resource,&s->visual,y,1,&s->ready,data_083A260C,0,0,owner);
            func_080DBDC8(s->visual,&s->x,&s->y);
            entry->state++;
        }
        break;
    case 0x101:
        if(!s->ready) break;
        func_080D7220(data_088F58BC,0,2,s->x,(s16)(s->y-8),0);
        s->other=func_080D4704(data_0894CC30,owner);
        s->object=func_080D3E9C(data_0894D69C,owner);
        s->effect=func_080D6098(s->x,s->y,0,1,4,s->unknown_10,data_083A2580,owner);
        if((s8)func_080DBC88(s->visual)>1) func_080D6194(s->effect,1);
        s->final=func_080DFD8C(data_083A2610,1,4,0,owner);
        entry->state++;
        break;
    case 0x102:
        s->effect=func_080D6134(s->effect);
        if(s->effect) break;
        s->other=func_080D4774(s->other);
        if(s->other) break;
        s->object=func_080D3F08(s->object);
        if(s->object) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        s->count=func_080D8858(s->resource,0);
        if(s->count<=0) entry->state=0x105;
        else {func_080D8CD4(s->resource); entry->state++;}
        break;
    case 0x103:
        if((u8)func_080D8B4C()==0) {s->timer=10; entry->state++;}
        break;
    case 0x104:
        func_080E0570(s->handles,2);
        if(--s->timer) break;
        p.index=s->index;
        p.resource=func_080DD4A4(s->resource,(u8)p.index);
        position=!!s->handles[0];
        s->handles[position]=func_08005B6C(func_0810C730,0x28,&p,owner);
        s->timer=0x28;
        s->index++;
        if(s->index==s->count) entry->state++;
        break;
    case 0x105:
        if((u8)func_080DE1F0(s->visual) && (u8)func_080E0570(s->handles,2)) entry->state=2;
        break;
    }
    return 0;
}
