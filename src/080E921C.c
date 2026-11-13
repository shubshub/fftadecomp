#include "ffta.h"
#include "control_flags.h"
// Target: 0x080E921C..0x080E93B4, 408 bytes.
typedef struct {u16 state; u16 unknown_2; void *resource; u8 unknown_8[12]; s16 mode; u16 argument; u32 unknown_18;} Descriptor;
typedef struct {u8 mode,count,idx,timer,argument; u8 unknown_5[3]; void *children[2]; void *intro; void *resource;} State;
extern u8 data_083983D8[],data_088EA0D8[],data_088E9C14[],data_0600FFC0[];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *,int);
extern void *func_080D3AF8(void);
extern void func_08000B68(void *,int,void *,int);
extern void func_080D45D0(const void *,int,int,int,int);
extern void func_08003620(int);
extern int func_080035A8(int);
extern u8 func_080E0570(void **,int);
extern void *func_080DD4A4(void *,int);
extern void *func_08005B6C(void *,int,void *,void *);
extern void func_080E8F3C(void);
int func_080E921C(void *owner,Descriptor *desc,State *s)
{
    Descriptor child;
    switch(desc->state) {
    case 0: {
        int arg;
        s->mode=desc->mode!=0x23;
        s->argument=desc->argument;
        s->resource=desc->resource;
        arg=5;
        if(s->argument) arg=0;
        s->intro=func_080E03F8(s->resource,data_083983D8,arg,1,0,owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->intro=func_080E05DC(s->intro);
        if(s->intro) break;
        s->count=func_080D8858(s->resource,0);
        if(!s->count) { desc->state=2; break; }
        func_08000B68(func_080D3AF8(),0,data_0600FFC0,16);
        if(!s->mode) {
            func_080D45D0(data_088EA0D8,6,0,1,1);
            func_080D45D0(data_088EA0D8,7,1,1,1);
            func_080D45D0(data_088E9C14,8,1,2,1);
        }
        s->timer=1;
        s->idx=0;
        func_08003620(1);
        desc->state++;
        break;
    case 0x101: {
        u8 slot;
        func_080E0570(s->children,2);
        if(--s->timer) break;
        slot=!!s->children[0];
        child.mode=s->mode;
        child.argument=s->idx;
        child.resource=func_080DD4A4(s->resource,s->idx);
        s->children[slot]=func_08005B6C(func_080E8F3C,44,&child,owner);
        s->timer=62;
        s->idx++;
        if(s->idx==s->count) desc->state++;
        break;
    }
    case 0x102:
        if(func_080E0570(s->children,2)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            desc->state=2;
        }
        break;
    }
    return 0;
}
