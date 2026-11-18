#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    void *unknown_08;
    u8 unknown_0C[8];
    u16 field_14;
    u16 field_16;
} Descriptor080E1EE0;

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

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

struct AffineParameters080032F8 {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
};

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct {
    u16 timer;
    u8 style;
    u8 finished;
    u8 variant;
    u8 unknown_05;
    s16 x;
    s16 y;
    void *object;
    void *sprite;
    void *effect_child;
    void *particle_child;
    void *outputs[2];
    void *coordinate_child;
    void *event_child;
    void *record_child;
    void *secondary_object;
    InterpolationState rotation;
    RequestNode transfer;
} Work080E1EE0;

extern const u8 data_088F104C[];
extern const u8 data_0894DB48[];
extern const u8 data_08949F18[];
extern const u8 data_08395AA8[];
extern const void *const data_08395A4C[];
extern const SequenceEvent data_08395B8C[];
extern const SequenceEvent data_08395BA4[];
extern const s16 data_08395BE4[];
extern u16 data_03003920[];
extern u32 data_0600FFC0[];

extern void func_080DE10C(void *object, u16 command);
extern void *func_080DE4B0(void *object, u8 *result, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay,
                           void *parent);
extern void *func_080DBA5C(void *object);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void func_080D49FC(u32 index, u32 type, u32 flags, s16 x, s16 y);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u32 index);
extern void *func_080D3E9C(const void *resource, void *context);
extern void *func_080D4704(const void *, void *);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void **outputs, const void *entries, void *parent);
extern void *func_080DFD8C(const SequenceEvent *records, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080D4D2C(void *resource, u8 mode);
extern void *func_080D3F08(void *handle);
extern void *func_080D4774(void *task);
extern void *func_080D6134(void *handle);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08141868(const void *source, void *destination, u32 control);

extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_0800BC90(u8 index, u8 enabled, u8 value);
extern void func_08003620(u8 value);
extern void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);
extern void func_08141864(const struct BgAffineSrc *src, struct BgAffineDst *dst, s32 count);
extern void func_080032F8(const struct AffineParameters080032F8 *parameters, u32 layer);

static inline void fill_halfwords(const u16 *source, u16 *destination, u32 control)
{
    func_0814186C(source, destination, control);
}

u32 func_080E1EE0(void *task, Descriptor080E1EE0 *descriptor, Work080E1EE0 *work)
{
    struct BgAffineSrc src;
    union {
        struct BgAffineDst bios;
        struct AffineParameters080032F8 display;
    } dst;
    struct {
        u16 first;
        u16 second;
        u32 word;
    } fill;
    u16 *buffer;
    u16 *first;
    u16 *second;

    switch (descriptor->phase) {
    case 0:
        work->style = descriptor->field_14;
        work->variant = descriptor->field_16;
        work->object = descriptor->object;
        work->secondary_object = descriptor->unknown_08;
        func_08000B68(&work->transfer, 0, (u32)data_0600FFC0, 16);
        break;
    case 1:
        break;
    case 0x100: {
        u8 delay = 50;

        func_080DE10C(work->object, 0x3C);
        work->event_child = func_080DE4B0(work->object, &work->finished, 1,
                                          -1, 0, delay, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (work->event_child && !work->finished)
            break;
        func_080DBDC8(work->object, &work->x, &work->y);
        work->coordinate_child = func_080D6098(work->x, work->y, 0, 1,
            data_08395AA8[work->style], work->outputs,
            data_08395A4C[work->style], task);
        work->record_child = func_080DFD8C(data_08395B8C, 1, 4, 0, task);
        work->timer = 30;
        descriptor->phase++;
        break;
    case 0x102:
        if (work->timer) {
            work->timer--;
            break;
        }
        work->y -= 32;
        func_080D49FC(0, 2, 1, work->x, work->y);
        func_0800BC90(0, 0, 2);
        work->sprite = func_080D4B64(0, data_088F104C, 0xBA, 6);
        func_08003620(1);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;
            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        work->effect_child = func_080D3E9C(data_0894DB48, task);
        work->particle_child = func_080D4704(data_08949F18, task);
        func_080E0608(&work->rotation, 0, -128, 28);
        work->record_child = func_080DFD8C(data_08395BA4, 1, 4, 0, task);
        work->timer = 0;
        descriptor->phase++;
        break;
    case 0x103:
        func_080E064C(&work->rotation);
        src.texX = 0x2000;
        src.texY = 0x3000;
        src.scrX = work->x;
        src.scrY = work->y;
        src.sx = data_08395BE4[work->timer];
        src.sy = data_08395BE4[work->timer];
        src.alpha = (u16)work->rotation.current << 8;
        func_08141864(&src, &dst.bios, 1);
        func_080032F8(&dst.display, 2);
        work->timer++;
        if (func_080E0690(&work->rotation))
            descriptor->phase++;
        break;
    case 0x104:
        work->coordinate_child = func_080D6134(work->coordinate_child);
        if (work->coordinate_child)
            break;
        work->event_child = func_080DBA5C(work->event_child);
        if (work->event_child)
            break;
        work->effect_child = func_080D3F08(work->effect_child);
        if (work->effect_child)
            break;
        work->particle_child = func_080D4774(work->particle_child);
        if (work->particle_child)
            break;
        work->sprite = func_080D4D2C(work->sprite, 0);
        if (work->sprite)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_08003620(0);
        first = &fill.first;
        *first = 0;
        buffer = data_03003920;
        fill_halfwords(first, buffer, 0x01000040);
        second = &fill.second;
        *second = 0;
        buffer += 0x100;
        fill_halfwords(second, buffer, 0x01000070);
        fill.word = 0;
        func_08141868(&fill.word, data_0600FFC0, 0x01000010);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
