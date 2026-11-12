/* Target bytes: f0b54f464646c0b484b080468946161c098880204000814220d0814202dc00290cd030e10448814200d1bfe00130814200d101e127e100000101000049464868f0630448c23004490180682030802020708018e160380003ff7f00000022b05e0223f15e01220092321c08320192484a02924246039200220123e4f7effef0604448002500950195012103220023e5f7a9ff41484146e2f7e3fd30610821ff22e2f752fe3d484146e3f70efa70613c484146e3f709fab061032012f76bf9394f3f24231c8343181c3a1c423211781070391c433108783f200870032012f75af98443381c443001780470391c3b3108780d70013908780d70053108780d700139ff200870013908780d70381c3c3001780570391c413108780d70013908780120404208703988c022d201101c08433880301c1c30002140223c23eff747f9301c2830002140223623eff740f9062030710120002100224346e9f7f6fb70630020002100224346e9f7effbb063706b0121e8f7fcfbb06b0121e8f7f8fb0a4843460093012104220023eef7e2fc306449e0f4a43908cc468f08e4d7940868b2940884869408400900035ca53908351c1c35281ceff72df9706b0022b15e0223f25eb38be9f71ffc3079071c002f02d00138307158e0341c2834201ceff719f9b06b0022b15e0223f25e338de9f70bfc281ceff730f90006002845d0201ceff72af9000600283fd00a4c211c4a3108780f702188084808402080032012f7a7f821888143218049460888013008802be0000040090003ff9f0000706be8f775fb7063002820d1b06be8f76ffbb06300281ad1f068e4f751fef060002814d13069e2f735fd306100280ed17069e3f765f97061002808d1b069e3f75ff9b061002802d102204a461080002004b018bc9846a146f0bc02bc0847 */
#include "control_flags.h"
struct Event { u16 state, unknown_2; void *value; };
struct Tween { u16 value; u16 unknown_2; u32 unknown_4, unknown_8; };
struct State { s16 x,y; u8 delay; u8 unknown_5[3]; void *unknown_8; void *window,*image,*text1,*text2; struct Tween a,b; void *sprite1,*sprite2,*value,*effect; };
extern struct { u8 unknown_0[0xc2]; u16 field_c2; } data_03003860;
extern u8 data_0839A4F4[],data_088F46CC[],data_0894D7E4[],data_0894B268[],data_08948684[],data_0839A55C[];
extern void *func_080D6098(int,int,int,int,int,void *,void *,void *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D3E9C(void *,void *);
extern void func_080D3F84(void *,int,int);
extern void *func_080D4704(void *,void *);
extern int func_080035D0(int);
extern int func_080035A8(int);
extern void func_080E0608(struct Tween *,int,int,int);
extern void func_080E064C(struct Tween *);
extern u8 func_080E0690(struct Tween *);
extern void *func_080DAB84(int,int,int,void *);
extern void func_080D9BA8(void *,int);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void func_080DAC40(void *,int,int,int);
extern void *func_080D9B64(void *);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
int func_080F123C(void *owner,struct Event *event,struct State *s)
{
 switch(event->state) {
 case 0:
 s->value=event->value;
 data_03003860.field_c2=0x7fff;
 s->x=104; s->y=32;
 break;
 case 0x100:
 s->window=func_080D6098(s->x,s->y,0,1,1,&s->unknown_8,data_0839A4F4,owner);
 func_080D7220(data_088F46CC,1,3,0,0,0);
 s->image=func_080D3E9C(data_0894D7E4,owner);
 func_080D3F84(s->image,8,255);
 s->text1=func_080D4704(data_0894B268,owner);
 s->text2=func_080D4704(data_08948684,owner);
 g_control_flags_03000940.winin_lo=0x3f & ~func_080035D0(3);
 g_control_flags_03000940.winin_hi=0x3f;
 g_control_flags_03000940.winout_lo=0x3f & ~func_080035D0(3);
 g_control_flags_03000940.win0h_hi=0;
 g_control_flags_03000940.win0h_lo=0;
 g_control_flags_03000940.win0v_hi=0;
 g_control_flags_03000940.win0v_lo=255;
 g_control_flags_03000940.win1h_hi=0;
 g_control_flags_03000940.win1h_lo=0;
 g_control_flags_03000940.win1v_hi=0;
 g_control_flags_03000940.win1v_lo=255;
 g_control_flags_03000940.display |= 0x6000;
 func_080E0608(&s->a,0,64,60);
 func_080E0608(&s->b,0,64,54);
 s->delay=6;
 s->sprite1=func_080DAB84(1,0,0,owner);
 s->sprite2=func_080DAB84(0,0,0,owner);
 func_080D9BA8(s->sprite1,1);
 func_080D9BA8(s->sprite2,1);
 s->effect=func_080DFD8C(data_0839A55C,1,4,0,owner);
 event->state++;
 break;
 case 0x101:
 func_080E064C(&s->a);
 func_080DAC40(s->sprite1,s->x,s->y,s->a.value);
 if(s->delay) {s->delay--;break;}
 func_080E064C(&s->b);
 func_080DAC40(s->sprite2,s->x,s->y,s->b.value);
 if(func_080E0690(&s->a) && func_080E0690(&s->b)) {
 g_control_flags_03000940.bldcnt_lo=0;
 g_control_flags_03000940.display &= 0x9fff;
 g_control_flags_03000940.display &= ~func_080035A8(3);
 event->state++;
 }
 break;
 case 0x102:
 if((s->sprite1=func_080D9B64(s->sprite1)))break;
 if((s->sprite2=func_080D9B64(s->sprite2)))break;
 if((s->window=func_080D6134(s->window)))break;
 if((s->image=func_080D3F08(s->image)))break;
 if((s->text1=func_080D4774(s->text1)))break;
 if((s->text2=func_080D4774(s->text2)))break;
 event->state=2;
 break;
 }
 return 0;
}
