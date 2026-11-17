/* Complete target [0x080F1F1C, 0x080F21E6), 714 bytes including pools:
 * f0b557464e464546e0b487b080468a46151c098880267600b14217d0b14202dc00290bd048e10448814200d1c2e00130814200d128e13fe10101000051464868e865782028802020688035e100260822521991462b1c30330493281c3c300590291c48310691fd2080000090082001900027029703974648002178222023e3f791feb4004c44206001211ff7a7f8206801211ff79bf9701c0006060e052ee2d93c4800970197002102220023e5f72af939484146e1f764ff286238484146e2f793fb686236484146e2f78efba86235484146e2f789fbe862a86a0121e2f7d2fbe86a0121e2f7cefb2f4e311c423108783f243f200870022011f7dcfa8443301c443001780470311c3b3108780f70013908780f70053108780f7001390878ff200870318880229201101c084330800498002138222823eef7d9fa05980021c8228c23eef7d3fa80225200069800213c23eef7ccfa0020002100224346e8f784fd6865124b40460090002002210022e7f787fba8650e4841460091012104220023edf776fe286652461088013093e0000020ab4f08a45b8f0828db9408c0b59408a0b59408b0b5940840090003eca6390898a83908281c3c30eef7bafa2c1c4834201ceef7b5fa201ceef7d4fa0006002805d0201c0021321c3c23eef787fa2e1c08362178aa8f1206120e2b79301cfff789fe2879013028710006000e8b2801d9002028712c1c3034201ceef7b3fa000600280fd1201ceef78bfa686d0023e95e0223ea5e2b8e80240094e8f79bfd686de7f724fd286ae1f7d9fe286200283bd1686ae2f709fb011c6962002934d10c4c221c4a321078117021880a4808402080022011f713fa218881432180301c0621e3f7f2fe51460888013008801ce0000040090003ffdf0000686de7f7ddfc6865002811d1a86de7f7d7fc041cac65002c0ad1a86ae2f7d2faac62e86ae2f7cefaec62022052461080002007b038bc9846a146aa46f0bc02bc0847
 */
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 state;
    u16 unknown_02;
    void *value;
} Event080F1F1C;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080F1F1C;

typedef struct {
    s16 x;
    s16 y;
    u8 frame;
    u8 unknown_05[3];
    void *orbs[6];
    void *image;
    void *text1;
    void *text2;
    void *text3;
    Interpolation080F1F1C width;
    Interpolation080F1F1C radius;
    Interpolation080F1F1C angle;
    void *sprite;
    void *task;
    void *payload;
    void *effect;
} State080F1F1C;

extern const u8 data_084FAB20[];
extern const u8 data_088F5BA4[];
extern const u8 data_0894DB28[];
extern const u8 data_0894B5C0[];
extern const u8 data_0894B5A0[];
extern const u8 data_0894B5B0[];
extern const u8 data_0839A6EC[];
extern const u8 data_0839A898[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_080110F8(void *object, u8 enabled);
extern void func_080112E8(void *object, u8 enabled);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D4704(const void *data, void *parent);
extern void func_080D47A0(void *object, u8 enabled);
extern u16 func_080035D0(u8 index);
extern u16 func_080035A8(u8 index);
extern void func_080E0608(Interpolation080F1F1C *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(Interpolation080F1F1C *state);
extern u8 func_080E0690(Interpolation080F1F1C *state);
extern void *func_080DAB84(u8 first, u8 second, u8 third, void *parent);
extern void *func_080D979C(u8, u8, u8, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080F1E20(void **objects, u8 angle, u8 radius, u8 style);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void func_080D9B98(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void func_080D5F74(void **objects, u16 count);
extern void *func_080D9B64(void *);
extern void func_080D4768(void *);

u32 func_080F1F1C(void *owner, Event080F1F1C *event, State080F1F1C *s)
{
    switch (event->state) {
    case 0:
        s->payload = event->value;
        s->x = 120;
        s->y = 32;
        break;
    case 0x100: {
        u8 i;

        for (i = 0; i < 6; i++) {
            s->orbs[i] = func_080D5CC0(data_084FAB20, 0, 120, 32, 0x3F4, 8, 0, 0);
            func_080110F8(s->orbs[i], 1);
            func_080112E8(s->orbs[i], 1);
        }
        func_080D7220(data_088F5BA4, 0, 2, 0, 0, 0);
        s->image = func_080D3E9C(data_0894DB28, owner);
        s->text1 = func_080D4704(data_0894B5C0, owner);
        s->text2 = func_080D4704(data_0894B5A0, owner);
        s->text3 = func_080D4704(data_0894B5B0, owner);
        func_080D47A0(s->text2, 1);
        func_080D47A0(s->text3, 1);
        g_control_flags_03000940.winin_lo = 0x3F;
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 255;
        g_control_flags_03000940.display |= 0x2000;
        func_080E0608(&s->width, 0, 56, 40);
        func_080E0608(&s->radius, 0, 200, 140);
        func_080E0608(&s->angle, 0, 256, 60);
        s->sprite = func_080DAB84(0, 0, 0, owner);
        s->task = func_080D979C(0, 2, 0, data_0839A6EC, owner);
        s->effect = func_080DFD8C(data_0839A898, 1, 4, 0, owner);
        event->state++;
        break;
    }
    case 0x101:
        func_080E064C(&s->radius);
        func_080E064C(&s->angle);
        if (func_080E0690(&s->angle))
            func_080E0608(&s->angle, 0, 256, 60);
        func_080F1E20(s->orbs, s->angle.current, s->radius.current, s->frame);
        if (++s->frame >= 140)
            s->frame = 0;
        if (!func_080E0690(&s->width)) {
            func_080E064C(&s->width);
            func_080DAC80(s->sprite, s->x, s->y, s->width.current, 0x80);
            func_080D9B98(s->sprite);
        }
        if ((s->image = func_080D3F08(s->image)))
            break;
        if ((s->text1 = func_080D4774(s->text1)))
            break;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.display &= 0xDFFF;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080D5F74(s->orbs, 6);
        event->state++;
        break;
    case 0x102:
        if ((s->sprite = func_080D9B64(s->sprite)))
            break;
        if ((s->task = func_080D9B64(s->task)))
            break;
        func_080D4768(s->text2);
        s->text2 = 0;
        func_080D4768(s->text3);
        s->text3 = 0;
        event->state = 2;
        break;
    }
    return 0;
}
