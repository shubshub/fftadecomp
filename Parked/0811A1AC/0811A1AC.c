#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x0811A1AC, 0x0811A488), 732 bytes including literals.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *input;
    u16 unknown_08[7];
    u16 mode;
} Descriptor0811A1AC;

typedef struct {
    s16 value;
    u16 unknown_02;
    s32 unknown_04;
    s32 unknown_08;
} Motion0811A1AC;

typedef struct {
    u8 mode;
    u8 unknown_01;
    u16 delay;
    s16 x;
    s16 y;
    void *input;
    void *object;
    void *coordinate_result;
    void *sprite;
    void *effect_task;
    u8 unknown_1c[8];
    void *particle_task;
    void *initial_task;
    void *object_task;
    void *record_task;
    Motion0811A1AC zoom;
} Payload0811A1AC;

typedef struct {
    s32 texture_x;
    s32 texture_y;
    s16 screen_x;
    s16 screen_y;
    s16 scale_x;
    s16 scale_y;
    u16 angle;
} AffineSource0811A1AC;

typedef struct {
    s16 pa;
    s16 pb;
    s16 pc;
    s16 pd;
    s32 x;
    s32 y;
} AffineTransform0811A1AC;

extern const u8 data_083A65A4[];
extern const u8 data_088F378C[];
extern const u8 data_0894DEBC[];
extern const u8 data_083A6618[];
extern const u8 data_083A65D4[];
extern const u8 data_083A6604[];
extern const u8 data_083A6620[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void func_0800BC90(u32, u32, u32);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BDA4(void *, u8);
extern void func_08003620(u8);
extern void func_08141864(const AffineSource0811A1AC *, AffineTransform0811A1AC *, int);
extern void func_080032F8(const AffineTransform0811A1AC *, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(Motion0811A1AC *, s16, s16, u16);
extern u8 func_080E0690(Motion0811A1AC *);
extern void func_080E064C(Motion0811A1AC *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DD580(void *);
extern void *func_080DBA5C(void *);
extern void *func_080DC498(void *, u8, u8, u16, void *);
extern void *func_080D6134(void *);

u32 func_0811A1AC(void *task, Descriptor0811A1AC *descriptor,
                  Payload0811A1AC *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 mode;

            payload->mode = descriptor->mode;
            payload->input = descriptor->input;
            mode = 4;
            if (payload->mode)
                mode = 0;
            payload->initial_task = func_080E03F8(payload->input,
                data_083A65A4, mode, 7, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (!func_080D8858(payload->input, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD4A4(payload->input, 0);
        func_080DC12C(payload->input, 0, 1);
        descriptor->phase++;
        break;
    case 0x101:
        {
            AffineSource0811A1AC src;
            AffineTransform0811A1AC dst;

            if (func_080D8B4C())
                break;
            payload->coordinate_result = func_080DD748(payload->object,
                &payload->x, &payload->y, 0);
            payload->y -= 12;
            func_080D49FC(0, 2, 1, payload->x, payload->y);
            func_0800BC90(0, 0, 2);
            payload->sprite = func_080D4B64(0, data_088F378C, 0x40, 6);
            func_0800BDA4(payload->sprite, 1);
            func_08003620(1);
            src.texture_x = 0x2000;
            src.texture_y = 0x2000;
            src.screen_x = payload->x;
            src.screen_y = payload->y;
            src.scale_x = payload->zoom.value;
            src.scale_y = payload->zoom.value;
            src.angle = 0;
            func_08141864(&src, &dst, 1);
            func_080032F8(&dst, 2);
            {
                u32 mask = func_080035A8(2);
                u16 flags = g_control_flags_03000940.display;

                flags |= mask;
                g_control_flags_03000940.display = flags;
            }
            payload->effect_task = func_080D3E9C(data_0894DEBC, task);
            payload->record_task = func_080DFD8C(data_083A6618, 1, 4, 0, task);
            func_080E0608(&payload->zoom, 0x100, 0x800, 60);
            payload->delay = 30;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (payload->delay) {
            payload->delay--;
            break;
        }
        if (!func_080E0690(&payload->zoom)) {
            AffineSource0811A1AC src;
            AffineTransform0811A1AC dst;

            func_080E064C(&payload->zoom);
            src.texture_x = 0x2000;
            src.texture_y = 0x2000;
            src.screen_x = payload->x;
            src.screen_y = payload->y;
            src.scale_x = payload->zoom.value;
            src.scale_y = payload->zoom.value;
            src.angle = 0;
            func_08141864(&src, &dst, 1);
            func_080032F8(&dst, 2);
            break;
        }
        payload->effect_task = func_080D3F08(payload->effect_task);
        if (payload->effect_task)
            break;
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        payload->particle_task = func_080D6098(payload->x, payload->y + 12,
            0, 1, 2, payload->unknown_1c, data_083A65D4, task);
        payload->object_task = func_080DCFE4(payload->object, data_083A6604,
            12, 0, 2, task, 0);
        if (func_080DD580(payload->object)) {
            payload->record_task = func_080DFD8C(data_083A6620, 1, 4, 0, task);
            descriptor->phase++;
        } else {
            descriptor->phase = 0x104;
        }
        break;
    case 0x103:
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task)
            break;
        payload->object_task = func_080DC498(payload->coordinate_result,
            0x10, 12, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->particle_task = func_080D6134(payload->particle_task);
        if (payload->particle_task)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
