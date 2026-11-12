/* Complete target bytes: f0b54f464646c0b484b080460d1c161c2b88064883426bd083420edc012b35d0012b05dc002b15d076e10000010100008020400083422cd06ee10548834200d100e1834272db0130834200d150e163e103010000e98ab1726868706306220906002900d00022e86802210840002801d001203072706b04490093434601930023d7f780fc306347e114113a08caf7d8fe42e1306bd7f768fd3063002800d03be1706bcbf71df80006040e002c00d031e15827307a002800d02427706bd4f7a4fcf060391cd5f7e8fa307a00280cd1f068b11d0094019402944246039202220223d5f7acfcb06300e034802888013012e1b06b002803d0b079002800d10ce13088002805d0013830800004002800d003e1054843460093012104220023d7f7fcf8306528880130f6e0b8113a08706b0021cff758fe0006002800d1ebe0706b0021d4f776fc7061d4f783fc031cf068834205d1b11c321d181cd3f7fcf806e07069b11c321d0023d4f7b5fd3061b0880438002189460024b0800222b05e0423f15e03220092321c18320192294a02924246039200220123cdf745fa7062254800940194002102220023cef700fb224f391c423108783f243f2008700220faf6cefc8443381c443001780470391c3b3108784b460b70013908780b70053108780b7001390878ff200870388880229201111c08433880301c4030202100222823d7f7c9fc0020002100224346d1f781fff0640121d0f78fff09484146cbf705f9b06207484146cbf734fdf0622888013072e05c113a08cc468f0840090003e4d7940818c09408341c4034201cd7f7c5fcf06cd2f79af8f06c0223f15eb2880c3a120412142388d1f7b2ff201cd7f7d7fc0006002851d01a4c21881a48084020800220faf658fc218881432180b06acbf702f9b062002840d1f06acbf732fd021cf262002a39d17069104900924346019302920c220023d4f75cf9f0637069d4f726fc0006002808d0094841460091012104220023d7f721f83065288801301be0000040090003ff9f0000a4113a08c0113a08f06cd0f7fdfef06400280dd1706acdf7dff97062002807d1f06bd2f76dfef063002801d102202880002004b018bc9846a146f0bc02bc0847 */
#include "control_flags.h"
typedef struct { u16 state; u16 unknown_2; void *object; u32 unknown_8; u32 flags; u8 unknown_10[6]; u16 mode; } Event;
typedef struct { u16 timer; s16 x,y; u8 ready,unknown_7,flag,unknown_9,mode,unknown_b; void *actor,*position,*target; u8 unknown_18[12]; void *effect,*a,*b,*transition,*object,*opening,*closing; u16 movement[6]; void *sprite,*script; } State;
extern u8 data_083A1114[],data_083A115C[],data_083A11A4[],data_083A11B8[],data_083A11C0[],data_088F46CC[],data_0894C018[],data_0894D7E4[];
extern void *func_080E03F8(void*,void*,int,int,int,void*);
extern void func_080D38B4(void);
extern void *func_080E05DC(void*);
extern u8 func_080D3B54(void*);
extern void *func_080DD47C(void*);
extern void func_080DE10C(void*,int);
extern void *func_080DE4B0(void*,u8*,int,int,int,int,int,void*);
extern void *func_080DFD8C(void*,int,int,int,void*);
extern u8 func_080D8858(void*,int);
extern void *func_080DD4A4(void*,int);
extern void *func_080DD4C4(void*);
extern void func_080DBDC8(void*,s16*,s16*);
extern void *func_080DD748(void*,s16*,s16*,int);
extern void *func_080D6098(int,int,int,int,int,void*,void*,void*);
extern void func_080D7220(void*,int,int,int,int,int);
extern u32 func_080035D0(int);
extern void func_080E0608(void*,int,int,int);
extern void *func_080DAB84(int,int,int,void*);
extern void func_080D9BA8(void*,int);
extern void *func_080D3E9C(void*,void*);
extern void *func_080D4704(void*,void*);
extern void func_080E064C(void*);
extern void func_080DADFC(void*);
extern void func_080DAC40(void*,int,int,int);
extern u8 func_080E0690(void*);
extern u32 func_080035A8(int);
extern void *func_080D3F08(void*);
extern void *func_080D4774(void*);
extern void *func_080DCFE4(void*,void*,int,int,int,void*,int);
extern u8 func_080DD580(void*);
extern void *func_080D9B64(void*);
extern void *func_080D6134(void*);
extern void *func_080DBA5C(void*);
int func_08108A74(void *context, Event *event, State *s)
{
    void *actor;
    switch(event->state) {
    case 0: {
        int speed;
        s->mode=event->mode;
        s->object=event->object;
        speed=6;
        if(s->mode) speed=0;
        if(event->flags & 2) s->flag=1;
        s->transition=func_080E03F8(s->object,data_083A1114,speed,0,0,context);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100: {
        int speed;
        s->transition=func_080E05DC(s->transition);
        if(s->transition) break;
        if(func_080D3B54(s->object)) { event->state=2; break; }
        speed=0x58;
        if(s->flag) speed=0x24;
        s->actor=func_080DD47C(s->object);
        func_080DE10C(s->actor,speed);
        if(!s->flag) s->opening=func_080DE4B0(s->actor,&s->ready,2,2,0,0,0,context);
        else s->timer=0;
        event->state++;
        break;
    }
    case 0x101:
        if(s->opening && !s->ready) break;
        if(s->timer && --s->timer) break;
        s->script=func_080DFD8C(data_083A11B8,1,4,0,context);
        event->state++;
        break;
    case 0x102:
        if(!func_080D8858(s->object,0)) { event->state=2; break; }
        s->target=func_080DD4A4(s->object,0);
        actor=func_080DD4C4(s->target);
        if(actor==s->actor) func_080DBDC8(actor,&s->x,&s->y);
        else s->position=func_080DD748(s->target,&s->x,&s->y,0);
        s->y-=4;
        s->effect=func_080D6098(s->x,s->y,0,1,3,s->unknown_18,data_083A115C,context);
        func_080D7220(data_088F46CC,0,2,0,0,0);
        g_control_flags_03000940.winin_lo=0x3f;
        g_control_flags_03000940.winout_lo=0x3f & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi=0;
        g_control_flags_03000940.win0h_lo=0;
        g_control_flags_03000940.win0v_hi=0;
        g_control_flags_03000940.win0v_lo=0xff;
        g_control_flags_03000940.display |= 0x2000;
        func_080E0608(s->movement,0x20,0,0x28);
        s->sprite=func_080DAB84(0,0,0,context);
        func_080D9BA8(s->sprite,1);
        s->a=func_080D3E9C(data_0894D7E4,context);
        s->b=func_080D4704(data_0894C018,context);
        event->state++;
        break;
    case 0x103:
        func_080E064C(s->movement);
        func_080DADFC(s->sprite);
        func_080DAC40(s->sprite,s->x,(s16)(s->y-12),s->movement[0]);
        if(!func_080E0690(s->movement)) break;
        g_control_flags_03000940.display &= 0x9fff;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        s->a=func_080D3F08(s->a);
        if(s->a) break;
        s->b=func_080D4774(s->b);
        if(s->b) break;
        s->closing=func_080DCFE4(s->target,data_083A11A4,12,0,0,context,0);
        if(func_080DD580(s->target)) s->script=func_080DFD8C(data_083A11C0,1,4,0,context);
        event->state++;
        break;
    case 0x104:
        s->sprite=func_080D9B64(s->sprite);
        if(s->sprite) break;
        s->effect=func_080D6134(s->effect);
        if(s->effect) break;
        s->closing=func_080DBA5C(s->closing);
        if(s->closing) break;
        event->state=2;
        break;
    }
    return 0;
}
