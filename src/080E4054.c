// Target: complete [0x080E4054, 0x080E41E4), 400 bytes.
#include "control_flags.h"
typedef struct {u16 state; u16 unknown_2; void *resource; u8 unknown_8[12]; s16 selector; u16 flag;} Descriptor;
typedef struct {u8 count,timer,delay,mode,flag; u8 unknown_5[3]; void *children[2]; void *b; void *d; void *resource;} State;
typedef struct {u16 state; u16 unknown_2; void *resource; u8 unknown_8[12]; u16 timer; u16 mode; u32 unknown_18;} ChildDescriptor;
extern u8 data_08396884[];
extern u8 data_0894D690[];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *,int);
extern void *func_080D3E9C(void *,void *);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(u8);
extern u8 func_080E0570(void **,int);
extern void *func_080DD4A4(void *,int);
extern int func_080E3E84(void *,Descriptor *,void *);
extern void *func_08005B6C(void *,int,void *,void *);
int func_080E4054(void *owner,Descriptor *desc,State *s)
{
    ChildDescriptor child;
    switch(desc->state) {
    case 0: {
        int count,kind;
        s->flag=desc->flag;
        s->resource=desc->resource;
        s->mode=0;
        if(desc->selector==0x65) s->mode=1;
        else if(desc->selector==0x109) s->mode=2;
        count=5;
        if(s->flag) count=0;
        kind=1;
        if(s->mode==2) kind=7;
        s->d=func_080E03F8(s->resource,data_08396884,count,kind,0,owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->d=func_080E05DC(s->d);
        if(s->d) break;
        s->count=func_080D8858(s->resource,0);
        if(s->mode==2) s->count--;
        if(s->count) {
            s->b=func_080D3E9C(data_0894D690,owner);
            g_control_flags_03000940.display |= func_080035A8(2);
            s->delay=1;
            s->timer=0;
            desc->state++;
            break;
        }
        desc->state=2;
        break;
    case 0x101: {
        u8 slot;
        func_080E0570(s->children,2);
        if(--s->delay) break;
        slot=!!s->children[0];
        child.timer=s->timer;
        child.mode=s->mode;
        child.resource=func_080DD4A4(s->resource,s->timer);
        s->children[slot]=func_08005B6C(func_080E3E84,48,&child,owner);
        s->delay=54;
        s->timer++;
        if(s->timer==s->count) desc->state++;
        break;
    }
    case 0x102:
        s->b=func_080D3F08(s->b);
        if(s->b) break;
        if(func_080E0570(s->children,2)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            desc->state=2;
        }
        break;
    }
    return 0;
}
