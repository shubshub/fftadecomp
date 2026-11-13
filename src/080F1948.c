/* 0x080F1948: complete 420-byte target, including literal pools. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    s16 current, remaining, error, step, period, distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *owner;
} Descriptor;

typedef struct {
    s16 x, y;
    u8 index;
    u8 unknown_05[3];
    void *background;
    void *animation;
    void *first_effect;
    void *second_effect;
    void *owner;
    void *task;
    InterpolationState motion;
} Payload;

typedef struct {
    int x, y;
    s16 screen_x, screen_y, scale_x, scale_y;
    u16 angle;
} AffineSource;

typedef struct {
    s16 pa, pb, pc, pd;
    int x, y;
} AffineDestination;

extern const u8 data_088F104C[], data_0894DB48[];
extern const u8 data_089492DC[], data_0894B268[], data_0839A584[];
extern const u16 data_0839A50C[];
extern u16 g_control_flags_03000940;
extern void func_080D49FC(int, int, int, s16, s16);
extern void func_0800BC90(int, int, int);
extern void *func_080D4B64(int, const void *, int, int);
extern void func_08003620(int);
extern unsigned int func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern void func_08141864(const AffineSource *, AffineDestination *, int);
extern void func_080032F8(const AffineDestination *, int);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D4D2C(void *, int);

unsigned int func_080F1948(void *task, Descriptor *descriptor, Payload *payload)
{
    AffineSource source;
    AffineDestination destination;

    switch (descriptor->phase) {
    case 0:
        payload->owner = descriptor->owner;
        payload->x = 120;
        payload->y = 40;
        break;
    case 0x100:
        func_080D49FC(0, 2, 1, payload->x, payload->y);
        func_0800BC90(0, 0, 2);
        payload->background = func_080D4B64(0, data_088F104C, 0xba, 6);
        func_08003620(1);
        {
            unsigned int mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->animation = func_080D3E9C(data_0894DB48, task);
        payload->first_effect = func_080D4704(data_089492DC, task);
        payload->second_effect = func_080D4704(data_0894B268, task);
        func_080E0608(&payload->motion, 0, -128, 28);
        payload->task = func_080DFD8C(data_0839A584, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->motion);
        source.x = 0x2000;
        source.y = 0x3000;
        source.screen_x = payload->x;
        source.screen_y = payload->y;
        source.scale_x = data_0839A50C[payload->index];
        source.scale_y = data_0839A50C[payload->index];
        source.angle = payload->motion.current << 8;
        func_08141864(&source, &destination, 1);
        func_080032F8(&destination, 2);
        payload->index++;
        if (func_080E0690(&payload->motion))
            descriptor->phase++;
        break;
    case 0x102:
        payload->animation = func_080D3F08(payload->animation);
        if (payload->animation)
            break;
        payload->first_effect = func_080D4774(payload->first_effect);
        if (payload->first_effect)
            break;
        payload->second_effect = func_080D4774(payload->second_effect);
        if (payload->second_effect)
            break;
        payload->background = func_080D4D2C(payload->background, 0);
        if (payload->background)
            break;
        {
            unsigned int mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        func_08003620(0);
        descriptor->phase = 2;
        break;
    }
    return 0;
}
