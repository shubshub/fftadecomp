#include "ffta.h"
#include "control_flags.h"

/* Complete target [0x080FA76C, 0x080FACF8), 1420 bytes.
 * Target bytes:
 * f0b5474680b48eb0071c8846161c0b8882204000834200d142e1834219dc8025
 * 6d00ab4259d0ab4204dc002b2dd0012b50d0a1e281204000834279d0834200dd
 * c4e0f078002800d196e2b069def78cfa5ae284204000834200d1b4e1834207dc
 * 0238834200d161e1834200dd98e122e185204000834200d11ce2834200dae1e1
 * 0130834200d14be276e2337042461421505eb82801d1012030704246d18ab170
 * 5568b56109483478201802780906002900d000220649a0004018016800930197
 * 281c0023e5f7e2fd706155e26cc9390864c93908d9f738f84ee27069e5f7c8fe
 * 7061002800d047e2b069d9f77df90006040e002c03d00220414608803ce2b069
 * 311c0831084af31c0093084b019305230293039404970123e3f770fbf0614246
 * 1088013027e200000780000034ca3908def756f90006002800d01de2b0690021
 * e2f7fafd3061311db21d0023e2f746fff060b068e2f73cff0006002802d0f088
 * 0838f0800421705ef18840390904091401220092321c24320192114b32789200
 * d21812680292039700220123dbf7cefbf062dbf73ffc0b493078800040180068
 * 391cd9f7f9fe706307480097012104220023e5f735fa3064424610880130dae1
 * d0c93908d8c9390838ca3908f06adbf7fbfbf062002800d0cee1706bd9f714ff
 * 041c7463002c00d0c6e10420335ef0884038000400140090002002210122daf7
 * 47f800200021022211f78cf91e4932789000401801681d485200121812880020
 * 0623daf7e9f83062012008f743fe022008f704fe164a11880143118031780422
 * b35ef288403a134808180078000205901148091808780002069005a803814281
 * 8581c58104820aa9012246f045ff0aa8022108f78bfc0948391cd9f759fa3063
 * 1e20707040e10000e0c93908e8c939084009000348ca39084aca3908e4d99408
 * 7078013870700006002800d064e1424610880130108032780420345ef388403b
 * 17497078400040180021455e1548101800780002059014481218107800020690
 * 05a8002204814381011c802040008881081cc58102820aa9012246f0fdfe0aa8
 * 022108f743fc7078013070700006000e0e2800d830e14246108801302be10000
 * ecc9390848ca39084aca390831780420355ef388403b174a7078013840008018
 * 02885242144808180078000205901348091808780002069005a8002405814381
 * 011c802040008881081cc28104820aa9012246f0c1fe0aa8022108f707fc7078
 * 013870700006002800d0f5e018207070bae00000ecc9390848ca39084aca3908
 * 7078013870700006002800d0e4e0301c44300822524200210423e5f76ffd4246
 * 10880130d7e0371c4437381ce5f788fd31780420345ef288403a38881218164d
 * 164808180078000205901548091808780002069005a8002304814281011c8020
 * 40008881081cc58103820aa9012246f073fe0aa8022108f7b9fb381ce5f782fd
 * 0006002800d1a7e008214942381c20220a23e5f733fd67e000ffffff48ca3908
 * 4aca3908341c4434201ce5f749fd31780422b55ef288403a20881218124e1348
 * 08180078000205901148091808780002069005a8002305814281011c80204000
 * 8881081cc68103820aa9012246f034fe0aa8022108f77afb201ce5f743fd0006
 * 002869d030e0000000ffffff48ca39084aca39080422b05e0622b15e02220092
 * 321c24320192134a0292039700220123dbf72cfaf06230693278910089188900
 * 0d4a8918042200920197162202920c221623e2f7c1f9f0630848009701210422
 * 0023e5f78df83064414608880130088032e0000070c939080cca390840ca3908
 * b068e3f7affa0006002825d0306bd9f735f9306300281fd1306a0021daf740f8
 * 3062002818d1022008f778fc0e4a118881431180002008f7adfcf06adbf734fa
 * f062002808d1f06be0f7c2fef063002802d102204246108000200eb008bc9846
 * f0bc02bc0847000040090003
 */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 option;
} Descriptor080FA76C;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080FA76C;

typedef struct {
    u8 kind;
    u8 timer;
    u8 option;
    u8 ready;
    s16 x;
    s16 y;
    void *output;
    void *coordinate_result;
    void *child;
    void *loader;
    void *object;
    void *scene;
    void *background;
    void *particle_output;
    u32 unknown_28;
    void *particle;
    void *task_a;
    void *task_b;
    u32 unknown_38;
    void *attachment;
    void *effect;
    Interpolation080FA76C fade;
} State080FA76C;

typedef struct {
    s32 texture_x;
    s32 texture_y;
    s16 screen_x;
    s16 screen_y;
    s16 scale_x;
    s16 scale_y;
    u16 angle;
} AffineSource080FA76C;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineTransform080FA76C;

extern const void *const data_0839C964[];
extern const u8 data_0839C96C[];
extern const u8 data_0839C970[];
extern const void *const data_0839C9D0[];
extern const void *const data_0839C9D8[];
extern const void *const data_0839C9E0[];
extern const u16 data_0839C9E8[];
extern const s16 data_0839C9EC[];
extern const u8 data_0839CA0C[][20];
extern const u8 data_0839CA34[];
extern const u8 data_0839CA38[];
extern const u8 data_0839CA40[];
extern const u8 data_0839CA48[];
extern const u8 data_0839CA4A[];
extern const u8 data_0894D9E4[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD73C(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D6180(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080D4774(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void func_0800BC90(u32, u32, u32);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_08003620(u8);
extern u32 func_080035A8(u8);
extern void func_08141864(const AffineSource080FA76C *, AffineTransform080FA76C *, int);
extern void func_080032F8(const AffineTransform080FA76C *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(Interpolation080FA76C *, s16, s16, u16);
extern void func_080E064C(Interpolation080FA76C *);
extern u8 func_080E0690(Interpolation080FA76C *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern u8 func_080DE1F0(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080DBA5C(void *);

/* The ROM carries this block five times, instruction for instruction, at
 * 0x080FA9A8, 0x080FAA22, 0x080FAA98, 0x080FAB3C and 0x080FABBA.  Each copy
 * reads kind, x, y and scale_y once, in that order, ahead of the first store
 * to the source block (0x080FAA22-0x080FAA36), and all five share the one
 * source block at sp+0x14 and the one result at sp+0x28.  The horizontal
 * scale 0x100 and the zero angle are in every copy.  func_080D6E30
 * (src/080D6E30.c) is the out-of-line relative that takes them as arguments. */
static inline void set_affine_080FA76C(u8 kind, s16 x, s16 y, s16 scale_y)
{
    AffineSource080FA76C src;
    AffineTransform080FA76C dst;

    src.texture_x = data_0839CA48[kind] << 8;
    src.texture_y = data_0839CA4A[kind] << 8;
    src.screen_x = x;
    src.screen_y = y;
    src.scale_x = 0x100;
    src.scale_y = scale_y;
    src.angle = 0;
    func_08141864(&src, &dst, 1);
    func_080032F8(&dst, 2);
}

u32 func_080FA76C(void *owner, Descriptor080FA76C *desc, State080FA76C *state)
{
    u8 count;

    switch (desc->state) {
    case 0:
        state->kind = 0;
        if (desc->kind == 0xB8)
            state->kind = 1;
        state->option = desc->option;
        state->object = desc->object;
        count = data_0839C96C[state->kind];
        if (state->option)
            count = 0;
        state->loader = func_080E03F8(state->object,
            data_0839C964[state->kind], count, 0, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->loader = func_080E05DC(state->loader);
        if (state->loader)
            break;
        if (func_080D3B54(state->object)) {
            desc->state = 2;
            break;
        }
        state->scene = func_080DDF68(state->object, &state->output, 0x8007, 1,
            &state->ready, data_0839CA34, 5, 0, owner);
        desc->state++;
        break;
    case 0x101:
        if (state->ready) {
            func_080D8CD4(state->object);
            desc->state++;
        }
        break;
    case 0x102:
        if (func_080D8B4C())
            break;
        state->child = func_080DD4A4(state->object, 0);
        state->coordinate_result = func_080DD748(state->child, &state->x,
            &state->y, 0);
        if (func_080DD73C(state->output))
            state->y -= 8;
        state->particle = func_080D6098(state->x, state->y - 0x40, 0, 1, 1,
            &state->particle_output, data_0839C9D0[state->kind], owner);
        func_080D6180(state->particle);
        state->task_b = func_080D4704(data_0839C9D8[state->kind], owner);
        state->effect = func_080DFD8C(data_0839CA38, 1, 4, 0, owner);
        desc->state++;
        break;
    case 0x103:
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->task_b = func_080D4774(state->task_b);
        if (state->task_b)
            break;
        func_080D49FC(0, 2, 1, state->x, state->y - 0x40);
        func_0800BC90(0, 0, 2);
        state->background = func_080D4B64(0, data_0839C9E0[state->kind],
            data_0839C9E8[state->kind], 6);
        func_08003620(1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;
            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        set_affine_080FA76C(state->kind, state->x, state->y - 0x40, 0x100);
        state->task_a = func_080D3E9C(data_0894D9E4, owner);
        state->timer = 30;
        desc->state++;
        break;
    case 0x104:
        if (--state->timer)
            break;
        desc->state++;
        /* fall through: 0x080FAA20 runs on into 0x080FAA22 */
    case 0x105:
        set_affine_080FA76C(state->kind, state->x, state->y - 0x40,
            data_0839C9EC[state->timer]);
        if (++state->timer >= 15)
            desc->state++;
        break;
    case 0x106:
        set_affine_080FA76C(state->kind, state->x, state->y - 0x40,
            -data_0839C9EC[state->timer - 1]);
        if (--state->timer == 0) {
            state->timer = 24;
            desc->state++;
        }
        break;
    case 0x107:
        if (--state->timer)
            break;
        func_080E0608(&state->fade, 0, -8, 4);
        desc->state++;
        break;
    case 0x108:
        func_080E064C(&state->fade);
        set_affine_080FA76C(state->kind, state->x,
            state->y - 0x40 + state->fade.current, -0x100);
        if (func_080E0690(&state->fade)) {
            func_080E0608(&state->fade, -8, 32, 10);
            desc->state++;
        }
        break;
    case 0x109:
        func_080E064C(&state->fade);
        set_affine_080FA76C(state->kind, state->x,
            state->y - 0x40 + state->fade.current, -0x100);
        if (func_080E0690(&state->fade))
            desc->state++;
        break;
    case 0x10A:
        state->particle = func_080D6098(state->x, state->y, 0, 1, 2,
            &state->particle_output, data_0839C970, owner);
        state->attachment = func_080DCFE4(state->child,
            data_0839CA0C[state->kind], 12, 22, 4, owner, 22);
        state->effect = func_080DFD8C(data_0839CA40, 1, 4, 0, owner);
        desc->state++;
        break;
    case 0x10B:
        if (!func_080DE1F0(state->output))
            break;
        state->task_a = func_080D3F08(state->task_a);
        if (state->task_a)
            break;
        state->background = func_080D4D2C(state->background, 0);
        if (state->background)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        state->attachment = func_080DBA5C(state->attachment);
        if (state->attachment)
            break;
        desc->state = 2;
        break;
    }
    return 0;
}
