/* Target bytes: f0b582b0041c0f1c161c39880548814243d081420ddc012934d0012904dc002918d04fe1010100008020400081422cd048e10748814200d1bbe0814274db0130814200d1f4e00130814200d126e139e10301000001227270f170b17031701420395e0648814201d13270b27004480092062100220023b8f79ffa23e177010000a4b48e08b7f79cfa1ce17078211c02f013fe30613888013013e1306902f02efe3061002800d00de1201c02f0b5fd7061307800280ad1301c2030002120221e23c4f796fa00480ee0086c3a08301c2030002191223c23c4f78bfa1048211cb7f7d1fef0610e480094012104220023c3f741fef062f078002807d10a4b0094022002210022bdf73efbb06100211320307371730120b07138880130d2e064dd9408006c3a08f06b3a08351c2035281cc4f781fa7069318c0906090e321c0c32331c0d33b41d0094b4780194fff7adfe281cc4f792fa0006002800d1b3e03c20b0803078012822d10220e7f612fa0c4c2188814321800320e7f60bfa21888143094801402180211c4a310878ff2008704e342078102020700020b7f786fc024890e040090003ffdf0000050100003888013087e07069318c0906090e321c0c32331c0d33b41d0094b4780194fff76dfef07800281ad0b188282917d80220084000280ad00449488a02304a8a4882c88a023009e00000400900030c49488a02384a8a4882c88a0238ca8ac882b0880138b0800004002856d1301c2030202100221e23c4f7e6f9388801304be0000040090003351c2035281cc4f7fdf97069bef7d2fd7069318c0906090e321c0c32331c0d33b41d0094b4780194fff726fe281cc4f70bfa000600282dd00220e7f691f9094c21888143002521800320e7f689f9218881430548014021804a34207825703888013016e040090003ffdf0000f069b7f727fef06100280dd17069bdf74ffc7061002807d1b069bdf749fcb061002801d102203880002002b0f0bc02bc0847 */
#include "ffta.h"
#include "control_flags.h"
struct State {
 u8 mode, enabled, option, shake;
 u16 timer;
 u8 active, unknown_07[5];
 u8 x, y, unknown_0e[2];
 void *transition, *object, *child, *effect;
 u16 animation[6];
 void *sprite;
};
extern u8 data_088EB4A4[], data_083A6C08[], data_0894DD64[], data_083A6C00[], data_083A6BF0[];
extern void func_080D45D0(void *, int, int, int, int);
extern void func_080D35D8(void);
extern void *func_0811ECD0(int, void *);
extern void *func_0811ED14(void *);
extern void *func_0811EC30(void *);
extern void func_080E0608(void *, int, int, int);
extern void *func_080D3E9C(void *, void *);
extern void *func_080DFD8C(void *, int, int, int, void *);
extern void *func_080D979C(int, int, int, void *, void *);
extern void func_080E064C(void *);
extern void func_0811BEC0(void *, u8, u8 *, u8 *, u8 *, u8);
extern u8 func_080E0690(void *);
extern int func_080035A8(int);
extern void func_080D3AC0(int);
extern void func_080DADFC(void *);
extern void *func_080D3F08(void *);
extern void *func_080D9B64(void *);
int func_0811C018(void *owner, u16 *command, struct State *state)
{
 switch (*command) {
 case 0:
  state->enabled = 1;
  state->shake = 0;
  state->option = 0;
  state->mode = 0;
  if (((s16 *)command)[10] == 375) {
   state->mode = 1;
   state->option = 1;
  }
  func_080D45D0(data_088EB4A4,6,0,0,1);
  break;
 case 1:
  func_080D35D8();
  break;
 case 256:
  state->transition = func_0811ECD0(state->enabled,owner);
  ++*command;
  break;
 case 257:
  state->transition = func_0811ED14(state->transition);
  if (state->transition == 0) {
   state->object = func_0811EC30(owner);
   if (!state->mode) {
    func_080E0608(state->animation,0,32,30);
    state->sprite = func_080DFD8C(data_083A6C08,1,4,0,owner);
   } else {
    func_080E0608(state->animation,0,145,60);
    state->effect = func_080D3E9C(data_0894DD64,owner);
    state->sprite = func_080DFD8C(data_083A6C00,1,4,0,owner);
   }
   if (!state->shake)
    state->child = func_080D979C(2,2,0,data_083A6BF0,owner);
   state->x = 19;
   state->y = 0;
   state->active = 1;
   ++*command;
  }
  break;
 case 258: {
  int next_command;
  func_080E064C(state->animation);
  func_0811BEC0(state->object,(u8)state->animation[0],&state->x,&state->y,&state->active,state->option);
  if (func_080E0690(state->animation)) {
   state->timer = 60;
   if (state->mode == 1) {
    g_control_flags_03000940.display &= ~func_080035A8(2);
    g_control_flags_03000940.display &= ~func_080035A8(3);
    g_control_flags_03000940.display &= 0xdfff;
    g_control_flags_03000940.bldcnt_lo = 255;
    g_control_flags_03000940.bldy_lo = 16;
    func_080D3AC0(0);
    next_command = 261;
   } else {
    next_command = *command + 1;
   }
   *command = next_command;
  }
  break;
 }
 case 259:
  func_0811BEC0(state->object,(u8)state->animation[0],&state->x,&state->y,&state->active,state->option);
  if (state->shake && state->timer <= 40) {
   if (state->timer & 2) {
    g_control_flags_03000940.bg2hofs += 2;
    g_control_flags_03000940.bg3hofs += 2;
   } else {
    g_control_flags_03000940.bg2hofs -= 2;
    g_control_flags_03000940.bg3hofs -= 2;
   }
  }
  if (--state->timer == 0) {
   func_080E0608(state->animation,32,0,30);
   ++*command;
  }
  break;
 case 260:
  func_080E064C(state->animation);
  func_080DADFC(state->object);
  func_0811BEC0(state->object,(u8)state->animation[0],&state->x,&state->y,&state->active,state->option);
  if (func_080E0690(state->animation)) {
   g_control_flags_03000940.display &= ~func_080035A8(2);
   g_control_flags_03000940.display &= ~func_080035A8(3);
    g_control_flags_03000940.display &= 0xdfff;
   g_control_flags_03000940.bldcnt_lo = 0;
   ++*command;
  }
  break;
 case 261:
  state->effect = func_080D3F08(state->effect);
  if (!state->effect) {
   state->object = func_080D9B64(state->object);
   if (!state->object) {
    state->child = func_080D9B64(state->child);
    if (!state->child) *command = 2;
   }
  }
  break;
 }
 return 0;
}
