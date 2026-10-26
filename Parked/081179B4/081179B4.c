#include "ffta.h"

struct Descriptor {
    u16 phase;
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
    u16 delay;
    u8 unknown_02[6];
    void *child;
    struct InterpolationState first_motion;
    struct InterpolationState second_motion;
    void *first_window;
    void *second_window;
};

struct DisplayState {
    u16 control;
    u8 unknown_02[0x38];
    u16 window0_right : 8;
    u16 window0_left : 8;
    u16 window1_right : 8;
    u16 window1_left : 8;
    u8 window0_bottom;
    u16 window0_top : 8;
    s16 window1_bottom : 8;
    u16 window1_top : 8;
    u16 window0_layers : 8;
    u16 window1_layers : 8;
    u16 outside_layers : 8;
    u8 unknown_45[5];
    u16 blend_control : 8;
};

extern struct DisplayState g_control_flags_03000940;
extern const u8 data_088F46CC[];
extern const u8 data_0894D69C[];
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u32 func_080035D0(u8);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void *func_080DAB84(u8, s16, s16, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080DAC40(void *, s16, s16, u16);
extern u32 func_080035A8(u8);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);

/* Target: complete [0x081179B4, 0x08117B9A), 486 bytes, 211 instructions.
 * Unmatched candidate; see README.md in this directory. */
u32 func_081179B4(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100:
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        g_control_flags_03000940.window0_layers = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.window1_layers = 0x3f;
        g_control_flags_03000940.outside_layers = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.window0_left = 0;
        g_control_flags_03000940.window0_right = 0;
        g_control_flags_03000940.window0_top = 0;
        g_control_flags_03000940.window0_bottom = 0xff;
        g_control_flags_03000940.window1_left = 0;
        g_control_flags_03000940.window1_right = 0;
        g_control_flags_03000940.window1_top = 0;
        g_control_flags_03000940.window1_bottom = -1;
        g_control_flags_03000940.control |= 0x6000;
        func_080E0608(&payload->first_motion, 0, 64, 60);
        func_080E0608(&payload->second_motion, 0, 64, 54);
        payload->delay = 6;
        payload->first_window = func_080DAB84(1, 0, 0, task);
        payload->second_window = func_080DAB84(0, 0, 0, task);
        func_080D9BA8(payload->first_window, 1);
        func_080D9BA8(payload->second_window, 1);
        payload->child = func_080D3E9C(data_0894D69C, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->first_motion);
        func_080DAC40(payload->first_window, 120, 80, payload->first_motion.current);
        if (payload->delay != 0) {
            payload->delay--;
            break;
        }
        func_080E064C(&payload->second_motion);
        func_080DAC40(payload->second_window, 120, 80, payload->second_motion.current);
        if (func_080E0690(&payload->first_motion) &&
            func_080E0690(&payload->second_motion)) {
            g_control_flags_03000940.blend_control = 0;
            g_control_flags_03000940.control &= 0x9fff;
            g_control_flags_03000940.control &= ~func_080035A8(2);
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->first_window = func_080D9B64(payload->first_window);
        if (payload->first_window != 0)
            break;
        payload->second_window = func_080D9B64(payload->second_window);
        if (payload->second_window != 0)
            break;
        payload->child = func_080D3F08(payload->child);
        if (payload->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
