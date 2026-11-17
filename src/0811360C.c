#include "ffta.h"
#include "control_flags.h"

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 value;
} Descriptor0811360C;

typedef struct {
    u8 unknown_00[8];
    u32 value;
    void *sprite;
    void *timeline;
    void *first_overlay;
    void *second_overlay;
    InterpolationState motion;
    void *record_task;
} Payload0811360C;

extern const u8 data_085055D0[];
extern const u8 data_088F5F08[];
extern const u8 data_0894D69C[];
extern const u8 data_0894BDD8[];
extern const u8 data_0894BDB4[];
extern const u8 data_083A37D0[];
extern u8 data_03003920[];
extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern void func_08011100(void *, u8);
extern u16 func_080035D0(u8);
extern u16 func_080035A8(u8);
extern void func_0814186C(const void *, void *, u32);
extern void func_080D7220(const void *, u8, u8, u16, u16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080D7468(const void *, u8, s16, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_08011428(void *);

/* Complete [0x0811360C, 0x081137BC): 432 bytes, 167 instructions. */
u32 func_0811360C(void *task, Descriptor0811360C *descriptor,
                  Payload0811360C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        payload->sprite = func_080D5CC0(data_085055D0, 1, 120, 112, 664, 6, 1, 0);
        func_08011100(payload->sprite, 2);
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.winout_hi = 0x3F;
        g_control_flags_03000940.display |= 0x8000;
        {
            /* CpuFill16(0, data_03003920, 0x20) */
            u16 zero = 0;

            func_0814186C(&zero, data_03003920, 0x01000010);
        }
        break;
    case 0x100:
        func_080D7220(data_088F5F08, 0, 2, 0, 0, 0);
        payload->timeline = func_080D3E9C(data_0894D69C, task);
        payload->first_overlay = func_080D4704(data_0894BDD8, task);
        payload->second_overlay = func_080D4704(data_0894BDB4, task);
        func_080E0608(&payload->motion, 0, -1, 5);
        payload->record_task = func_080DFD8C(data_083A37D0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->motion);
        func_080D7468(data_088F5F08, 2, 0, payload->motion.current);
        if (func_080E0690(&payload->motion))
            func_080E0608(&payload->motion, payload->motion.current,
                          payload->motion.current - 1, 5);
        payload->first_overlay = func_080D4774(payload->first_overlay);
        if (!payload->first_overlay) {
            payload->second_overlay = func_080D4774(payload->second_overlay);
            if (!payload->second_overlay)
                descriptor->phase++;
        }
        break;
    case 0x102:
        payload->timeline = func_080D3F08(payload->timeline);
        if (!payload->timeline) {
            func_08011428(payload->sprite);
            payload->sprite = 0;
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= 0x7FFF;
            g_control_flags_03000940.bldcnt_lo = 0;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
