#include "control_flags.h"
/* Target: 0x0810973C..0x0810998E, 594 bytes. */
typedef struct { u16 state; u16 unknown_02; u32 object; u8 unknown_08[12]; s16 kind; u16 mode; } Event;
typedef struct { u8 mode, count, kind, unknown_03, index, delay; s16 x,y; u16 unknown_0a; void *children[2]; u32 intro, layers[2], overlay, transition, effect, object, backdrop; } State;
typedef struct { u32 unknown_00; u32 object; u8 unknown_08[12]; u16 index; u16 unknown_16; u32 unknown_18; } Parameters;
extern u8 data_083A17C0[];
extern u32 data_083A17B8[];
extern u8 data_088F63C0[], data_0894DCA4[], data_0894DCB8[], g_object_08949554[], g_object_08949564[], data_0894AC40[], data_0894ACE0[], data_083A180C[], data_083A1838[];
extern u32 func_080E03F8(u32,u32,u32,u32,u32,void*);
extern void func_080D38B4(void);
extern u32 func_080E05DC(u32);
extern u32 func_080D8858(u32,u32);
extern void func_080D8C58(u32,s16*,s16*);
extern void func_080D7220(void*,u32,u32,s32,s32,u32);
extern u32 func_080D3E9C(void*,void*);
extern u32 func_080D4704(void*,void*);
extern void func_080D47A0(u32,u32);
extern u32 func_080D4724(void*,void*,u32);
extern u32 func_080D979C(u32,u32,u32,void*,void*);
extern u32 func_080DFD8C(void*,u32,u32,u32,void*);
extern u32 func_080D3F08(u32);
extern u32 func_080035A8(u32);
extern u32 func_080D9B64(u32);
extern void func_080D4938(u32*,u32);
extern u8 func_080E0570(void**,u32);
extern u32 func_080DD4A4(u32,u32);
extern void func_08109664(void);
typedef void Callback(void);
extern void *func_08005B6C(Callback *callback,u32 size,Parameters *parameters,void *owner);
u32 func_0810973C(void *owner, Event *event, State *s)
{
    Parameters parameters;
    u32 value;
    u8 slot;
    switch(event->state) {
    case 0:
        s->mode=event->mode;
        s->object=event->object;
        s->kind=0;
        if(event->kind==278) s->kind=1;
        value=data_083A17C0[s->kind];
        if(s->mode) value=0;
        s->transition=func_080E03F8(s->object,data_083A17B8[s->kind],value,1,0,owner);
        break;
    case 1: func_080D38B4(); break;
    case 256:
        s->transition=func_080E05DC(s->transition);
        if(s->transition) break;
        if(s->mode) {
            s->delay=1;
            s->count=func_080D8858(s->object,0);
            event->state=258;
            break;
        }
        func_080D8C58(s->object,&s->x,&s->y);
        func_080D7220(data_088F63C0,0,2,s->x,s->y,0);
        if(s->kind==0) s->intro=func_080D3E9C(data_0894DCA4,owner);
        else s->intro=func_080D3E9C(data_0894DCB8,owner);
        s->layers[0]=func_080D4704(g_object_08949554,owner);
        s->layers[1]=func_080D4704(g_object_08949564,owner);
        func_080D47A0(s->layers[0],1);
        func_080D47A0(s->layers[1],1);
        if(s->kind==0) s->overlay=func_080D4724(data_0894AC40,owner,40);
        else s->overlay=func_080D4724(data_0894ACE0,owner,40);
        s->effect=func_080D979C(0,2,0,data_083A180C,owner);
        s->backdrop=func_080DFD8C(data_083A1838,1,4,0,owner);
        event->state++;
        break;
    case 257:
        s->intro=func_080D3F08(s->intro);
        if(s->intro) break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        s->effect=func_080D9B64(s->effect);
        if(s->effect) break;
        func_080D4938(s->layers,3);
        s->delay=1;
        s->count=func_080D8858(s->object,0);
        if(s->count==0) event->state=259;
        else event->state++;
        break;
    case 258:
        func_080E0570(s->children,2);
        if(--s->delay) break;
        slot=!!s->children[0];
        parameters.object=func_080DD4A4(s->object,s->index);
        parameters.index=s->index;
        s->children[slot]=func_08005B6C(func_08109664,40,&parameters,owner);
        s->delay=40;
        s->index++;
        if(s->index==s->count) event->state++;
        break;
    case 259:
        if(func_080E0570(s->children,2)) event->state=2;
        break;
    }
    return 0;
}
