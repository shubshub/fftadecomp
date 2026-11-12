/* Target bytes: f0b54f464646c0b484b081468846161c0c888020400084422dd0844202dc002c0cd028e10448844200d1c9e00130844200d103e11fe100000101000041464868b060b11c321dbef7b3fdb0882038b080b0683c21c0f74effb068b11d0094019402944a46039203220223c1f715f9b06314203080ffe0b079002800d1fbe03088002805d0013830800004002800d0f2e04648002500950195012103220023b9f7b3ff43484946b6f7edfdf0600821ff22b6f75cfe0223f05e0422b15e01220092321c143201923b4a02924b46039300220023b8f7d5fe3061374849460091012104220023c2f746fdf0630320e6f664f9324f3f24221c8243101c3a1c423211781070391c433108783f2008700320e6f653f98443381c443001780470391c3b3108780d70013908780d70053108780d700139ff200870013908780d70381c3c3001780570391c413108780d70013908780120404208703988c023db01181c08433880301c1830182100221c23c3f740f9301c2430102100221c23c3f739f90120002100224b46bdf7f1fb30630020002100224b46bdf7eafb7063306b0121bcf7f7fb706b0121bcf7f3fb3ee0cc468f0890d69408246e3a083c6e3a0840090003341c1834201cc3f735f9351c2435281cc3f730f9306bbdf705fd706bbdf702fd306b0222b15e0423f25e338bbdf71cfc706b0222b15e0423f25eb38cbdf714fc201cc3f739f90006002834d0281cc3f733f9000600282ed00320e6f6b9f8054a11888143044801401180414608880130088020e040090003ff9f0000f068b6f757fdf060002816d13069b8f767fe3061002810d1306bbcf779fb306300280ad1706bbcf773fb7063002804d1b6f7ccfd022042461080002004b018bc9846a146f0bc02bc0847 */
#include "control_flags.h"
typedef struct { u16 state, unknown_2; void *object; } Event;
typedef struct { u16 value; u16 unknown_2[5]; } Transition;
typedef struct { u16 timer; s16 x,y; u8 ready,unknown_7; void *object,*resource,*effect; u32 auxiliary; Transition first,second; void *sprite1,*sprite2,*task,*other; } State;
extern u8 data_088F46CC[],data_0894D690[],data_083A6E24[],data_083A6E3C[];
extern void func_080DBDC8(void *,s16 *,s16 *);
extern void func_080DE10C(void *,int);
extern void *func_080DE4B0(void *,u8 *,int,int,int,int,int,void *);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D3E9C(void *,void *);
extern void func_080D3F84(void *,int,int);
extern void *func_080D6098(int,int,int,int,int,u32 *,void *,void *);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern unsigned func_080035D0(int);
extern unsigned func_080035A8(int);
extern void func_080E0608(Transition *,int,int,int);
extern void *func_080DAB84(int,int,int,void *);
extern void func_080D9BA8(void *,int);
extern void func_080E064C(Transition *);
extern void func_080DADFC(void *);
extern void func_080DAC40(void *,int,int,int);
extern u8 func_080E0690(Transition *);
extern void *func_080D3F08(void *);
extern void *func_080D6134(void *);
extern void *func_080D9B64(void *);
extern void func_080D4020(void);
int func_0811D218(void *owner,Event *event,State *s)
{
 switch(event->state) {
 case 0:
 s->object=event->object;
 func_080DBDC8(s->object,&s->x,&s->y);
 s->y-=32;
 func_080DE10C(s->object,60);
 s->task=func_080DE4B0(s->object,&s->ready,3,2,0,0,0,owner);
 s->timer=20;
 break;
 case 256:
 if(!s->ready) break;
 if(s->timer && --s->timer) break;
 func_080D7220(data_088F46CC,1,3,0,0,0);
 s->resource=func_080D3E9C(data_0894D690,owner);
 func_080D3F84(s->resource,8,255);
 s->effect=func_080D6098(s->x,s->y,0,0,1,&s->auxiliary,data_083A6E24,owner);
 s->other=func_080DFD8C(data_083A6E3C,1,4,0,owner);
 g_control_flags_03000940.winin_lo=63 & ~func_080035D0(3);
 g_control_flags_03000940.winin_hi=63;
 g_control_flags_03000940.winout_lo=63 & ~func_080035D0(3);
 g_control_flags_03000940.win0h_hi=0;
 g_control_flags_03000940.win0h_lo=0;
 g_control_flags_03000940.win0v_hi=0;
 g_control_flags_03000940.win0v_lo=255;
 g_control_flags_03000940.win1h_hi=0;
 g_control_flags_03000940.win1h_lo=0;
 g_control_flags_03000940.win1v_hi=0;
 g_control_flags_03000940.win1v_lo=-1;
 g_control_flags_03000940.display|=0x6000;
 func_080E0608(&s->first,24,0,28);
 func_080E0608(&s->second,16,0,28);
 s->sprite1=func_080DAB84(1,0,0,owner);
 s->sprite2=func_080DAB84(0,0,0,owner);
 func_080D9BA8(s->sprite1,1);
 func_080D9BA8(s->sprite2,1);
 event->state++;
 break;
 case 257:
 func_080E064C(&s->first);
 func_080E064C(&s->second);
 func_080DADFC(s->sprite1);
 func_080DADFC(s->sprite2);
 func_080DAC40(s->sprite1,s->x,s->y,s->first.value);
 func_080DAC40(s->sprite2,s->x,s->y,s->second.value);
 if(func_080E0690(&s->first) && func_080E0690(&s->second)) {
 g_control_flags_03000940.display &= ~func_080035A8(3);
 g_control_flags_03000940.display &= 0x9fff;
 event->state++;
 }
 break;
 case 258:
 if((s->resource=func_080D3F08(s->resource))) break;
 if((s->effect=func_080D6134(s->effect))) break;
 if((s->sprite1=func_080D9B64(s->sprite1))) break;
 if((s->sprite2=func_080D9B64(s->sprite2))) break;
 func_080D4020();
 event->state=2;
 break;
 }
 return 0;
}
