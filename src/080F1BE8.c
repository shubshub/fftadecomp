/* Target bytes (514): 70b584b0041c0e1c151c31880648814200d18be081420edc012900d1ece0012904dc002916d0e7e00101000080204000814216d0e0e00648814200d1a4e0814200da83e00130814200d1b5e0d4e00000030100007068e8627820288038206880cae00021685e0222a95e012200922a1c08320192274a0292039400220123e4f717fae8602448211ce2f714f9286100200021ff22231ce8f781ffa8620121e7f78fff1e4b191c4e31087800220a700c3908783f200870023108781f200870093908780a700139ff200870053108780a7001390878012040420870198880229201101c084318800e48211ce2f717fd68610c48211ce2f712fda8610b480094012104220023eef74ef82863142028713088013070e044a539087cdb94084009000368b29408dc92940894a53908287901382871000600285fd1281c1c30bc210b222823eef76dfc3088013054e02c1c1c34201ceef787fca86ae9f75cf8a86aab8b78211022e8f778ff201ceef79dfc0006002841d028692f21ff22e2f70ff9282028713088013036e02879013828710006030e002b30d106490a1c4a32107813700a880448104008803088013023e0000040090003ffdf0000a86ae7f7dffea862002819d12869e2f7abf82861002813d16869e2f7dbfc686100280dd1a869e2f7d5fca861002807d1e868e4f7aff9e860002801d102203080002004b070bc02bc0847 */
#include "control_flags.h"

typedef struct { u16 phase; u16 unknown_02; void *payload; } Message;
typedef struct { u16 value; u8 unknown_02[10]; } Transition;
typedef struct {
 s16 x, y;
 u8 timer; u8 unknown_05[3];
 u32 unknown_08;
 void *main_object, *object, *first, *second;
 Transition transition;
 void *effect, *payload, *extra;
} State;
extern const u8 data_0839A544[], data_0894DB7C[], data_0894B268[], data_089492DC[], data_0839A594[];
extern void *func_080D6098(int,int,int,int,int,void*,const void*,void*);
extern void *func_080D3E9C(const void*,void*);
extern void *func_080DAB84(int,int,int,void*);
extern void func_080D9BA8(void*,int);
extern void *func_080D4704(const void*,void*);
extern void *func_080DFD8C(const void*,int,int,int,void*);
extern void func_080E0608(Transition*,int,int,int);
extern void func_080E064C(Transition*);
extern void func_080DADFC(void*);
extern void func_080DAC40(void*,int,int,int);
extern u8 func_080E0690(Transition*);
extern void func_080D3F84(void*,int,int);
extern void *func_080D9B64(void*);
extern void *func_080D3F08(void*);
extern void *func_080D4774(void*);
extern void *func_080D6134(void*);
int func_080F1BE8(void *context, Message *message, State *state)
{
 switch(message->phase) {
 case 0:
  state->payload=message->payload;
  state->x=120; state->y=56;
  break;
 case 1: break;
 case 256:
  state->main_object=func_080D6098(state->x,state->y,0,1,1,&state->unknown_08,data_0839A544,context);
  state->object=func_080D3E9C(data_0894DB7C,context);
  state->effect=func_080DAB84(0,0,255,context);
  func_080D9BA8(state->effect,1);
  g_control_flags_03000940.bldy_lo=0;
  g_control_flags_03000940.winin_lo=63;
  g_control_flags_03000940.winout_lo=31;
  g_control_flags_03000940.win0h_hi=0;
  g_control_flags_03000940.win0h_lo=255;
  g_control_flags_03000940.win0v_hi=0;
  g_control_flags_03000940.win0v_lo=255;
  g_control_flags_03000940.display |= 0x2000;
  state->first=func_080D4704(data_0894B268,context);
  state->second=func_080D4704(data_089492DC,context);
  state->extra=func_080DFD8C(data_0839A594,1,4,0,context);
  state->timer=20;
  message->phase++;
  break;
 case 257:
  if (--state->timer==0) {
   func_080E0608(&state->transition,188,11,40);
   message->phase++;
  }
  break;
 case 258:
  func_080E064C(&state->transition);
  func_080DADFC(state->effect);
  func_080DAC40(state->effect,120,16,state->transition.value);
  if(func_080E0690(&state->transition)) {
   func_080D3F84(state->object,47,255);
   state->timer=40;
   message->phase++;
  }
  break;
 case 259:
  if(--state->timer==0) {
   g_control_flags_03000940.bldcnt_lo=0;
   g_control_flags_03000940.display &= 0xdfff;
   message->phase++;
  }
  break;
 case 260:
  if((state->effect=func_080D9B64(state->effect))) break;
  if((state->object=func_080D3F08(state->object))) break;
  if((state->first=func_080D4774(state->first))) break;
  if((state->second=func_080D4774(state->second))) break;
  if((state->main_object=func_080D6134(state->main_object))) break;
  message->phase=2;
  break;
 }
 return 0;
}
