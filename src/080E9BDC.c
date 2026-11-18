// func_080E9BDC: complete [0x080E9BDC, 0x080E9E28), 588 bytes.
// A phased BG2 affine zoom effect: it wraps the target object in a child task,
// enables the affine layer, then steps two interpolated scales through a
// keyframe table and feeds them to BgAffineSet every frame.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    s16 value;
    u8 unknown_02[10];
} Interpolation080E9BDC;

struct BgAffineSrc {
    s32 texX;
    s32 texY;
    s16 scrX;
    s16 scrY;
    s16 sx;
    s16 sy;
    u16 alpha;
};

struct BgAffineDst {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 dx;
    s32 dy;
};

typedef struct {
    u8 frame;
    u8 duration;
    u16 scale_x;
    u16 scale_y;
    u8 unknown_06[2];
} Keyframe080E9BDC;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *wrapper;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080E9BDC;

typedef struct {
    u8 selector;
    u8 keyframe;
    u16 timer;
    u8 unknown_04[2];
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    void *object;
    void *wrapper;
    Interpolation080E9BDC scale_x;
    Interpolation080E9BDC scale_y;
    Interpolation080E9BDC angle;
    struct BgAffineSrc affine;
    void *object_task;
} Payload080E9BDC;

extern const Keyframe080E9BDC data_08398830[];
extern const Keyframe080E9BDC data_08398858[];

extern void *func_080DD4C4(void *wrapper);
extern void *func_080DC1E8(void *object, u8 first, u8 second, u8 mode,
                          void *source, void *destination, void *parent);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080DBA5C(void *task);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern u16 func_080035A8(u8 layer);
extern void func_08003620(u8 value);
extern u16 func_080DD6E0(void *object);
extern void func_08141864(const struct BgAffineSrc *src,
                          struct BgAffineDst *dst, s32 count);
extern void func_080032F8(const struct BgAffineDst *dst, u8 layer);
extern u8 func_080DD580(void *wrapper);
extern void func_080E0608(Interpolation080E9BDC *state, s16 start, s16 end,
                          u8 duration);
extern u8 func_080E0690(Interpolation080E9BDC *state);
extern void func_080E064C(Interpolation080E9BDC *state);

static inline void step_keyframe_080E9BDC(Payload080E9BDC *payload,
                                          const Keyframe080E9BDC *table)
{
    if (table[payload->keyframe].frame == payload->timer) {
        if (payload->scale_x.value != table[payload->keyframe].scale_x)
            func_080E0608(&payload->scale_x, payload->scale_x.value,
                          table[payload->keyframe].scale_x,
                          table[payload->keyframe].duration);
        if (payload->scale_y.value != table[payload->keyframe].scale_y)
            func_080E0608(&payload->scale_y, payload->scale_y.value,
                          table[payload->keyframe].scale_y,
                          table[payload->keyframe].duration);
        payload->keyframe++;
    }
}

u32 func_080E9BDC(void *task, Descriptor080E9BDC *descriptor,
                  Payload080E9BDC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->wrapper = descriptor->wrapper;
        break;
    case 1:
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        break;
    case 0x100:
        payload->object = func_080DD4C4(payload->wrapper);
        payload->object_task = func_080DC1E8(payload->object, 1, 0, 6,
            (void *)0x0600F9C0, (void *)0x06005800, task);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        payload->timer = 20;
        descriptor->phase++;
        break;
    case 0x101: {
        struct BgAffineDst dst;
        u32 control;

        if (payload->timer != 0)
            payload->timer--;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task != 0)
            break;
        if (payload->timer != 0)
            break;
        control = func_08003A74(0x06005800);
        func_080034B8((u16)func_08003A80(0x0600C000) | 0x4000 | control | 0x80, 2);
        g_control_flags_03000940.display |= func_080035A8(2);
        func_08003620(1);
        payload->affine.texX = 0x1000;
        payload->affine.texY = 0x3000;
        if (func_080DD6E0(payload->object) == 0x51)
            payload->affine.texY = 0x2C00;
        payload->affine.scrX = payload->x;
        payload->affine.scrY = payload->y;
        payload->affine.sx = 0x100;
        payload->affine.sy = 0x100;
        payload->affine.alpha = 0;
        func_08141864(&payload->affine, &dst, 1);
        func_080032F8(&dst, 2);
        payload->timer = 60;
        descriptor->phase++;
        break;
    }
    case 0x102:
        if (--payload->timer != 0)
            break;
        payload->scale_x.value = 0x100;
        payload->scale_y.value = 0x100;
        payload->angle.value = 0;
        if (func_080DD580(payload->wrapper) != 0)
            descriptor->phase++;
        else
            descriptor->phase = 2;
        break;
    case 0x103: {
        struct BgAffineDst dst;

        if (payload->selector == 0)
            step_keyframe_080E9BDC(payload, data_08398830);
        else
            step_keyframe_080E9BDC(payload, data_08398858);
        if (!func_080E0690(&payload->scale_x)) {
            func_080E064C(&payload->scale_x);
            payload->affine.sx = payload->scale_x.value;
        }
        if (!func_080E0690(&payload->scale_y)) {
            func_080E064C(&payload->scale_y);
            payload->affine.sy = payload->scale_y.value;
        }
        func_08141864(&payload->affine, &dst, 1);
        func_080032F8(&dst, 2);
        payload->timer++;
        break;
    }
    }
    return 0;
}
