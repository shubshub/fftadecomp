#include "control_flags.h"
/* Target: 0x080E3C0C..0x080E3E82, 630 bytes. */
typedef struct {u16 state; u16 unknown_2; void *resource; u8 unknown_8[12]; u16 mode; u16 argument; u32 unknown_18;} Descriptor;
typedef struct {u8 argument,mode,count,timer,delay; u8 unknown_5[3]; void *children[2]; u8 unknown_10[20]; void *a,*b,*c,*d,*resource,*e;} State;
extern u8 data_083965DC[],data_083967D8[],data_083967F3[],data_083967F0[],data_083967DE[];
extern void *data_083965D0[],*data_083967C0[],*data_083967E4[];
extern u8 data_088F4674[],data_0894ABA0[],data_08396824[][8];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *,int);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D6098(int,int,int,int,int,void *,void *,void *);
extern void *func_080D3E9C(void *,void *);
extern void *func_080D4724(void *,void *,int);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern int func_080035A8(int);
extern u8 func_080E0570(void **,int);
extern void *func_080DD4A4(void *,int);
extern int func_080E3AC8(void *,Descriptor *,void *);
extern void *func_08005B6C(void *,int,void *,void *);
int func_080E3C0C(void *owner,Descriptor *desc,State *s)
{
    Descriptor child;
    switch(desc->state) {
    case 0: {
        int arg;
        void *resource;
        s->mode=desc->mode-2;
        s->argument=desc->argument;
        resource=desc->resource;
        s->resource=resource;
        arg=data_083965DC[s->mode];
        if(s->argument) arg=0;
        s->d=func_080E03F8(resource,data_083965D0[s->mode],arg,1,0,owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->d=func_080E05DC(s->d);
        if(s->d) break;
        if(s->argument) {
            s->delay=1;
            s->count=func_080D8858(s->resource,0);
            if(!s->count) desc->state=0x103;
            else desc->state=0x102;
            break;
        }
        func_080D7220(data_088F4674,0,2,120,64,0);
        s->a=func_080D6098(120,96,0,1,data_083967D8[s->mode],s->unknown_10,data_083967C0[s->mode],owner);
        s->b=func_080D3E9C(data_083967E4[s->mode],owner);
        s->c=func_080D4724(data_0894ABA0,owner,data_083967F3[s->mode]);
        s->e=func_080DFD8C(data_08396824[s->mode],1,4,0,owner);
        s->timer=data_083967F0[s->mode];
        desc->state++;
        break;
    case 0x101:
        s->a=func_080D6134(s->a);
        s->b=func_080D3F08(s->b);
        s->c=func_080D4774(s->c);
        if(--s->timer) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        s->delay=1;
        s->count=func_080D8858(s->resource,0);
        if(!s->count) desc->state=0x103;
        else desc->state++;
        break;
    case 0x102: {
        void **children;
        u8 slot;
        func_080E0570(children=s->children,2);
        if(--s->delay) break;
        slot=!!s->children[0];
        child.mode=s->mode;
        child.argument=s->timer;
        child.resource=func_080DD4A4(s->resource,s->timer);
        children[slot]=func_08005B6C(func_080E3AC8,48,&child,owner);
        s->delay=data_083967DE[s->mode];
        s->timer++;
        if(s->timer==s->count) desc->state++;
        break;
    }
    case 0x103:
        s->a=func_080D6134(s->a); if(s->a) break;
        s->b=func_080D3F08(s->b); if(s->b) break;
        s->c=func_080D4774(s->c); if(s->c) break;
        if(func_080E0570(s->children,2)) desc->state=2;
        break;
    }
    return 0;
}
