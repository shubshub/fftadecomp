#include "ffta.h"
#include "control_flags.h"

typedef struct Descriptor { u16 state, unknown_02; void *object; u32 unknown_08[3]; s16 kind; u16 mode; u32 unknown_18; } Descriptor;
typedef struct Payload { s16 x, y; u8 kind, mode; u16 unknown_06; void *object08, *object0c, *task10, *object14, *task18; u32 unknown_1c[4]; void *task2c, *task30, *task34, *task38, *task3c; } Payload;
extern u8 data_0839AC1C[], data_088EA990[], data_088F46F0[], data_08949D48[], data_08949FC0[], data_0894D69C[], data_0839AC58[], data_0839ACD0[], data_0839AD00[];
extern void *func_080E03F8(void *, void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(void *,int,int,int,int);
extern int func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern int func_080D8858(void *,int);
extern void func_080DBFFC(void *,int);
extern int func_080D8B4C(void);
extern void *func_080DD4A4(void *,int);
extern void *func_080DD748(void *,s16 *,s16 *,int);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D4704(void *,void *);
extern void *func_080D3E9C(void *,void *);
extern void *func_080D6098(int,int,int,int,int,void *,void *,void *);
extern void *func_080DCFE4(void *,void *,int,int,int,void *,int);
extern u32 func_080F378C(void *,void *,void *);
extern void *func_08005B6C(u32 (*callback)(void *,void *,void *),u16 size,void *descriptor,void *parent);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern int func_080035A8(int);
extern void *func_080DBA5C(void *);

/* Target 0x080F38C4..0x080F3B00, 572 bytes. */
u32 func_080F38C4(void *parent, Descriptor *descriptor, Payload *p)
{
    Descriptor child;
    void *object;
    int mode;
    switch (descriptor->state) {
    case 0:
        p->mode=descriptor->mode;
        p->object14=descriptor->object;
        switch(descriptor->kind) {
        case 0x51: p->kind=0; break;
        case 0x86: p->kind=1; break;
        case 0x70: p->kind=2; break;
        case 0xae: p->kind=3; break;
        }
        mode=5;
        if(p->mode) mode=0;
        p->task18=func_080E03F8(p->object14,data_0839AC1C,mode,7,0,parent);
        break;
    case 1: func_080D38B4(); break;
    case 0x100:
        p->task18=func_080E05DC(p->task18);
        if(p->task18) break;
        if(p->kind>1) func_080D45D0(data_088EA990,6,1,1,1);
        if((u8)func_080D3B54(p->object14)) { descriptor->state=2; break; }
        p->object08=func_080DD47C(p->object14);
        if(!(u8)func_080D8858(p->object14,0)) { descriptor->state=2; break; }
        func_080DBFFC(p->object14,0);
        descriptor->state++;
        break;
    case 0x101:
        if((u8)func_080D8B4C()) break;
        object=func_080DD4A4(p->object14,0);
        p->object0c=func_080DD748(object,&p->x,&p->y,0);
        func_080D7220(data_088F46F0,0,2,p->x,(s16)(p->y-4),0);
        if(p->kind<=1) p->task34=func_080D4704(data_08949D48,parent);
        else p->task34=func_080D4704(data_08949FC0,parent);
        p->task30=func_080D3E9C(data_0894D69C,parent);
        p->task2c=func_080D6098(p->x,p->y,0,1,4,p->unknown_1c,data_0839AC58,parent);
        if(p->kind<=1) p->task38=func_080DCFE4(object,data_0839ACD0,12,41,4,parent,80);
        else {
            child.object=p->object14;
            p->task10=func_08005B6C(func_080F378C,32,&child,parent);
        }
        p->task3c=func_080DFD8C(data_0839AD00,1,4,0,parent);
        descriptor->state++;
        break;
    case 0x102:
        p->task2c=func_080D6134(p->task2c);
        if(p->task2c) break;
        p->task30=func_080D3F08(p->task30);
        if(p->task30) break;
        p->task34=func_080D4774(p->task34);
        if(p->task34) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        p->task38=func_080DBA5C(p->task38);
        if(p->task38) break;
        p->task10=func_080E05DC(p->task10);
        if(p->task10) break;
        descriptor->state=2;
        break;
    }
    return 0;
}
