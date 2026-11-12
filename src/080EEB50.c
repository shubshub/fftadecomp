/* Target bytes: f0b54f464646c0b483b0071c8846161c0b888020400083422bd0834204dc002b0ed0012b22d0fae00448834200d1c1e00130834200d1c8e0f1e00000010100004146c88ab0704c68346203220006002800d00022044900930197201c0123f1f723fcf061dbe000002c993908e4f77afed5e0f069f1f70afd8146f061002800d0cde0306a0021e9f73ffe0006002803d1022042461080c2e0306a0021eef75afc041c311db21d0023eef7a6fdb060eef79dfd0006002802d0f0880838f08036490a20009001973c200290201c0c223c23eef7e0f9706231480421735ea02100914a46019200210222e8f7f2fa2c48391ce5f72cf9f0602b48391ce5f75bfd30610020002100223b1cebf794ff70610423f15e0623f25e2023ecf768f8224d291c423108783f243f200870022014f7a8fc8443281c443001780470291c3b31087848460870013908784a460a70053108780a7001390878ff200870298880239b01181c084328801148009001970220002101220123eaf706feb0610d480097012104220023f1f75af8b06248203080414608880130088042e05499390844558f08b8d8940890ac9408400900035099390868993908308801383080000400282ed1424610880130108029e03069e5f72afd3061002823d1f068e5f7eef8f06000281dd1022014f738fc114a11888143114801401180706aecf789fe706200280ed17069eaf707ff7061002808d1b069eaf701ffb061002802d1022043461880002003b018bc9846a146f0bc02bc0847000040090003ffdf0000 */
#include "control_flags.h"
struct Script { u16 state; u16 unknown_2; void *resource; u8 unknown_8[14]; u16 mode; };
struct State { u16 timer; u8 mode; u8 unknown_3; s16 x,y; void *position; void *a,*b,*c,*d,*e,*resource,*f,*g; };
extern u8 data_0839992C[],data_08399954[],data_088F5544[],data_0894D8B8[],data_0894AC90[],data_08399950[],data_08399968[];
extern void *func_080E03F8(void *,void *,int,int,int,void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *,int);
extern void *func_080DD4A4(void *,int);
extern void *func_080DD748(void *,s16 *,s16 *,int);
extern u8 func_080DD73C(void *);
extern void *func_080DCFE4(void *,void *,int,int,int,void *,int);
extern void func_080D7220(void *,int,int,int,int,int);
extern void *func_080D3E9C(void *,void *);
extern void *func_080D4704(void *,void *);
extern void *func_080DAB84(int,int,int,void *);
extern void func_080DAD3C(void *,int,int,int);
extern int func_080035D0(int);
extern int func_080035A8(int);
extern void *func_080D98D4(int,int,int,int,void *,void *);
extern void *func_080DFD8C(void *,int,int,int,void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void *func_080DBA5C(void *);
extern void *func_080D9B64(void *);
int func_080EEB50(void *owner,struct Script *script,struct State *s) {
 void *resource; void *object; int mode; int flags; u16 display;
 switch(script->state) {
 case 0:
 s->mode=script->mode;
 resource=script->resource;
 s->resource=resource;
 mode=3;
 if(s->mode) mode=0;
 s->e=func_080E03F8(resource,data_0839992C,mode,1,0,owner);
 break;
 case 1: func_080D38B4(); break;
 case 256:
 s->e=func_080E05DC(s->e);
 if(s->e) break;
 if(!func_080D8858(s->resource,0)){script->state=2;break;}
 object=func_080DD4A4(s->resource,0);
 s->position=func_080DD748(object,&s->x,&s->y,0);
 if(func_080DD73C(s->position)) s->y-=8;
 s->f=func_080DCFE4(object,data_08399954,12,60,10,owner,60);
 func_080D7220(data_088F5544,0,2,s->x,160,0);
 s->a=func_080D3E9C(data_0894D8B8,owner);
 s->b=func_080D4704(data_0894AC90,owner);
 s->c=func_080DAB84(0,0,0,owner);
 func_080DAD3C(s->c,s->x,s->y,32);
 g_control_flags_03000940.winin_lo=63;
 g_control_flags_03000940.winout_lo=63 & ~func_080035D0(2);
 g_control_flags_03000940.win0h_hi=0;
 g_control_flags_03000940.win0h_lo=0;
 g_control_flags_03000940.win0v_hi=0;
 g_control_flags_03000940.win0v_lo=255;
 g_control_flags_03000940.display |= 8192;
 s->d=func_080D98D4(2,0,1,1,data_08399950,owner);
 s->g=func_080DFD8C(data_08399968,1,4,0,owner);
 s->timer=72;
 script->state++;
 return 0;
 case 257: if(!--s->timer)script->state++;break;
 case 258:
 if(!(s->b=func_080D4774(s->b))) {
 if(!(s->a=func_080D3F08(s->a))) {
 flags=func_080035A8(2);
 display=g_control_flags_03000940.display & ~flags;
 g_control_flags_03000940.display=display & ~0x2000;
 if(!(s->f=func_080DBA5C(s->f))) {
 if(!(s->c=func_080D9B64(s->c))) {
 if(!(s->d=func_080D9B64(s->d))) {
 script->state=2;
 } } } } }

 break;
 }
 return 0;
}
