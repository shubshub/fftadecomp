// Target: complete [0x080FF5C8, 0x080FF76A), 418 bytes.
#include "ffta.h"
typedef struct {u16 state; u16 unknown_2; void *actor; u8 unknown_8[12]; u16 mode; u16 argument; u32 unknown_18;} Descriptor;
typedef struct {u8 argument,mode,count,unknown_3; u16 timer; u8 unknown_6[4]; u8 ready; u8 unknown_b; void *child_task; void *actor; void *sprite_state; void *initial_task; void *sprite_task; void *status_task;} State;
extern const u8 data_0839E2BC[],data_0839E354[],data_0839E340[];
extern void *func_080E03F8(void *,const void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *,void *,int,int,void *,const void *,int,int,void *);
extern void func_080DC12C(void *,int,int);
extern u8 func_080D8B4C(void);
extern int func_080D8858(void *,int);
extern void *func_080DD4A4(void *,int);
extern void *func_08005B6C(void *,int,void *,void *);
extern void *func_080DCFE4(void *,const void *,int,int,int,void *,int);
extern void *func_080E051C(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);
extern int func_080FF2C4(void *,Descriptor *,void *);
int func_080FF5C8(void *owner,Descriptor *desc,State *s)
{
    Descriptor child;
    switch(desc->state) {
    case 0: {
        void *actor;
        int arg;
        s->mode=desc->mode+86;
        s->argument=desc->argument;
        actor=desc->actor;
        s->actor=actor;
        arg=5;
        if(s->argument) arg=0;
        s->initial_task=func_080E03F8(actor,data_0839E2BC,arg,0,0,owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->initial_task=func_080E05DC(s->initial_task);
        if(s->initial_task) break;
        if(func_080D3B54(s->actor)) { desc->state=2; break; }
        s->status_task=func_080DDF68(s->actor,&s->sprite_state,0x8007,1,&s->ready,data_0839E354,5,0,owner);
        desc->state++;
        break;
    case 0x101:
        if(s->ready) {
            s->timer=16;
            desc->state++;
        }
        break;
    case 0x102:
        if(--s->timer) break;
        func_080DC12C(s->actor,0,2);
        s->timer=16;
        desc->state++;
        break;
    case 0x103:
        if(s->timer) {
            if(--s->timer) break;
        }
        if(func_080D8B4C()) break;
        s->count=func_080D8858(s->actor,0);
        if(!s->count) { desc->state=2; break; }
        {
            void *object=func_080DD4A4(s->actor,0);
            child.mode=s->mode;
            child.actor=object;
            s->child_task=func_08005B6C(func_080FF2C4,64,&child,owner);
            s->sprite_task=func_080DCFE4(object,data_0839E340,12,184,4,owner,184);
        }
        desc->state++;
        break;
    case 0x104:
        s->child_task=func_080E051C(s->child_task);
        if(s->child_task) break;
        if(!func_080DE244(s->sprite_state)) break;
        s->sprite_task=func_080DBA5C(s->sprite_task);
        if(!s->sprite_task) desc->state=2;
        break;
    }
    return 0;
}
