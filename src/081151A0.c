#include "control_flags.h"
/* Complete 824-byte target: f0b557464e464546e0b482b081468846161c09880648814200d1c7e081420edc012900d17ce1012904dc002916d077e10101000080204000814212d070e10648814200d130e1814200da0fe10130814200d151e164e10000030100000a2030805ee13088013800218a4630800004070c002f00d054e147484946bef73ffe30621821ff22bef7aefe434800970197012103220023c1f7f4ff0020002100224b46c5f7a0fc70623d4d291c423108783f243f2008700320eef6bbf98443281c443001780470291c3b31087852460a70013908780a70053108780a7001390878ff20087028888024a401211c08432880782070806020b080301c0830082100220423cbf7b2f9301c1430002160221023cbf7abf9706a338978216022c5f7c1fc706a738831895b1a190409140424325f60331b041b1400970197c5f774fc706a338971885b18190409140424325f60331b041b14009701240194c5f764fc706ac4f74bfc0f48e2300f49018071200121082232f0b4fbb0620c484f460097012104220023caf733fdf0624146088801300880c6e0000038dc9408cc468f084009000360380003ff7f000080393a08351c0835281ccbf77bf9301c1430cbf777f9706ac5f74cfd706a338978216022c5f768fc706ab38a191c7831090409146022d21a120412143389c5f75bfc706a738831895b1a190409140424325fb48a603c1b1b1b041b141427f45f009400240194c5f709fc706a338971885b18190409140424325fb48a603c1b1b1b041b141427f45f009401240194c5f7f5fb706ac4f7dcfb281ccbf755f90006002869d0b06a33f06df8b062002863d1306abef785fd306200285dd141460888013008800b48e2300b490180301c08300021c8223c23cbf7f3f8706ac5f7eafc06484946bef736fd3062424610880130108041e060380003ff7f0000ce393a08341c0834201ccbf7fdf8706a3389190449140904090c009178216022c5f70cfc706ac4f795fb201ccbf70ef90006002822d0054a1188054808401080444620880130208018e0000040090003ffdf0000306abef735fd306200280dd1706ac4f75dfb021c7262002a06d108484a3001780270022047463880002002b038bc9846a146aa46f0bc02bc0847000040090003 */
typedef struct { s16 current, remaining, error, step, period, distance; } Motion;
typedef struct { u16 delay; s16 x, y; u16 unknown_06; Motion first, second; void *child, *window, *effect, *other; } Payload;
extern const u8 data_0894DC38[], data_088F46CC[], data_083A3980[], data_083A39CE[];
extern struct { u8 unknown_00[0xE2]; u16 color; } data_03003860;
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void func_080D3F84(void *, int, int);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080DAB84(int, s16, s16, void *);
extern u32 func_080035D0(int);
extern void func_080E0608(Motion *, s16, s16, s16);
extern void func_080E064C(Motion *);
extern u8 func_080E0690(Motion *);
extern void func_080DAC40(void *, s16, s16, u16);
extern void func_080DABC4(void *, s16, s16, s16, s16, int);
extern void func_080D9B98(void *);
extern void func_080DADFC(void *);
extern void *func_08147A7C(int, int, int);
extern void *func_081484CC(void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void *func_080D9B64(void *);
u32 func_081151A0(void *task, u16 *phase, Payload *p)
{
 switch (*phase) {
 case 0: p->delay=10; break;
 case 1: break;
 case 0x100:
  if (--p->delay == 0) {
   p->child=func_080D3E9C(data_0894DC38,task);
   func_080D3F84(p->child,24,255);
   func_080D7220(data_088F46CC,1,3,0,0,0);
   p->window=func_080DAB84(0,0,0,task);
   g_control_flags_03000940.winin_lo=63;
   g_control_flags_03000940.winout_lo=63 & ~func_080035D0(3);
   g_control_flags_03000940.win0h_hi=0;
   g_control_flags_03000940.win0h_lo=0;
   g_control_flags_03000940.win0v_hi=0;
   g_control_flags_03000940.win0v_lo=255;
   g_control_flags_03000940.display |= 0x2000;
   p->x=120; p->y=96;
   func_080E0608(&p->first,8,0,4);
   func_080E0608(&p->second,0,96,16);
   func_080DAC40(p->window,120,96,p->first.current);
   func_080DABC4(p->window,(u16)p->x-(u16)p->first.current,p->y,(u16)p->x-(u16)p->first.current+96,0,0);
   func_080DABC4(p->window,(u16)p->x+(u16)p->first.current,p->y,(u16)p->x+(u16)p->first.current+96,0,1);
   func_080D9B98(p->window);
   data_03003860.color=0x7FFF;
   p->effect=func_08147A7C(0x71,1,8);
   p->other=func_080DFD8C(data_083A3980,1,4,0,task);
   ++*phase;
  }
  break;
 case 0x101:
  func_080E064C(&p->first);
  func_080E064C(&p->second);
  func_080DADFC(p->window);
  func_080DAC40(p->window,120,96,p->first.current);
  func_080DAC40(p->window,p->second.current+120,96-p->second.current,p->first.current);
  func_080DABC4(p->window,(u16)p->x-(u16)p->first.current,p->y,(u16)p->x-(u16)p->first.current-((u16)p->second.current-96),p->second.current,0);
  func_080DABC4(p->window,(u16)p->x+(u16)p->first.current,p->y,(u16)p->x+(u16)p->first.current-((u16)p->second.current-96),p->second.current,1);
  func_080D9B98(p->window);
  if (!func_080E0690(&p->first)) break;
  p->effect=func_081484CC(p->effect);
  if (p->effect) break;
  p->child=func_080D3F08(p->child);
  if (p->child) break;
  ++*phase;
 case 0x102:
  data_03003860.color=0x7FFF;
  func_080E0608(&p->first,0,200,60);
  func_080DADFC(p->window);
  p->child=func_080D3E9C(data_083A39CE,task);
  ++*phase;
  break;
 case 0x103:
  func_080E064C(&p->first);
  func_080DAC80(p->window,120,96,p->first.current,(u16)(p->first.current>>1));
  func_080D9B98(p->window);
  if (func_080E0690(&p->first)) {
   g_control_flags_03000940.display &= 0xDFFF;
   ++*phase;
  }
  break;
 case 0x104:
  p->child=func_080D3F08(p->child);
  if (p->child) break;
  p->window=func_080D9B64(p->window);
  if (!p->window) {
   g_control_flags_03000940.bldcnt_lo=0;
   *phase=2;
  }
  break;
 }
 return 0;
}
