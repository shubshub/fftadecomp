// Target: complete [0x081141EC, 0x0811435C), 368 bytes.
#include "control_flags.h"

struct Descriptor {
    u16 phase;
    u8 unknown_02[2];
    void **first;
    void **second;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u8 unknown_00[8];
    void **first;
    void **second;
    struct InterpolationState first_motion;
    struct InterpolationState second_motion;
};

extern const u8 data_08506970[];
extern const u8 data_085070E4[];
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011058(void *, s16);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);

u32 func_081141EC(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->first = descriptor->first;
        payload->second = descriptor->second;
        break;
    case 0x100:
        *payload->first = func_080D5CC0(data_08506970, 0, 352, 160, 930, 6, 1, 0);
        *payload->second = func_080D5CC0(data_085070E4, 0, 352, 160, 650, 6, 1, 0);
        func_08011058(*payload->second, -1);
        func_080E0608(&payload->first_motion, 360, 240, 40);
        func_080E0608(&payload->second_motion, 352, 240, 40);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 120;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 160;
        g_control_flags_03000940.winin_lo = 47;
        g_control_flags_03000940.winout_lo = 63;
        g_control_flags_03000940.display |= 0x2000;
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->first_motion);
        func_080E064C(&payload->second_motion);
        func_080107D4(*payload->first, payload->first_motion.current, 160, 0);
        func_080107D4(*payload->second, payload->second_motion.current, 160, 0);
        if (func_080E0690(&payload->first_motion)) {
            g_control_flags_03000940.display &= 0xdfff;
            descriptor->phase++;
        }
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
