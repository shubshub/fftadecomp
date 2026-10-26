#include "ffta.h"

/* Target: complete [0x0811AB44, 0x0811ACF2), 430 bytes including literals. */
struct Descriptor0811AB44 {
    u16 phase;
};

struct Interpolation0811AB44 {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload0811AB44 {
    u16 delay;
    u8 unknown_02[6];
    void *child;
    struct Interpolation0811AB44 first_motion;
    struct Interpolation0811AB44 second_motion;
    void *first_window;
    void *second_window;
};

struct Display0811AB44 {
    u16 flags;
    u8 unknown_02[0x38];
    u8 field_3a;
    u8 field_3b;
    u8 field_3c;
    u8 field_3d;
    u8 field_3e;
    u8 field_3f;
    s8 field_40;
    u8 field_41;
    u8 field_42;
    u8 field_43;
    u8 field_44;
    u8 unknown_45[5];
    u8 field_4a;
};

extern struct Display0811AB44 g_control_flags_03000940;
extern const u8 data_0894D97C[];
extern void func_080E0608(struct Interpolation0811AB44 *, s16, s16, s16);
extern void func_080E064C(struct Interpolation0811AB44 *);
extern u8 func_080E0690(struct Interpolation0811AB44 *);
extern void *func_080DAB84(u8, s16, s16, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080DAC40(void *, s16, s16, u16);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);

u32 func_0811AB44(void *task, struct Descriptor0811AB44 *descriptor,
                  struct Payload0811AB44 *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100:
        g_control_flags_03000940.field_42 = 31;
        g_control_flags_03000940.field_43 = 63;
        g_control_flags_03000940.field_44 = 31;
        g_control_flags_03000940.field_3b = 0;
        g_control_flags_03000940.field_3a = 0;
        g_control_flags_03000940.field_3f = 0;
        g_control_flags_03000940.field_3e = 255;
        g_control_flags_03000940.field_3d = 0;
        g_control_flags_03000940.field_3c = 0;
        g_control_flags_03000940.field_41 = 0;
        g_control_flags_03000940.field_40 = -1;
        g_control_flags_03000940.flags |= 0x6000;
        func_080E0608(&payload->first_motion, 0, 160, 36);
        func_080E0608(&payload->second_motion, 0, 160, 30);
        payload->delay = 6;
        payload->first_window = func_080DAB84(1, 0, 0, task);
        payload->second_window = func_080DAB84(0, 0, 0, task);
        func_080D9BA8(payload->first_window, 1);
        func_080D9BA8(payload->second_window, 1);
        payload->child = func_080D3E9C(data_0894D97C, task);
        descriptor->phase++;
        break;
    case 0x101:
        func_080E064C(&payload->first_motion);
        func_080DAC40(payload->first_window, 120, 64,
                     payload->first_motion.current);
        if (payload->delay != 0) {
            payload->delay--;
            break;
        }
        func_080E064C(&payload->second_motion);
        func_080DAC40(payload->second_window, 120, 64,
                     payload->second_motion.current);
        if (func_080E0690(&payload->first_motion) &&
            func_080E0690(&payload->second_motion)) {
            g_control_flags_03000940.field_4a = 0;
            g_control_flags_03000940.flags &= 0x9fff;
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->first_window = func_080D9B64(payload->first_window);
        if (payload->first_window == 0) {
            payload->second_window = func_080D9B64(payload->second_window);
            if (payload->second_window == 0) {
                payload->child = func_080D3F08(payload->child);
                if (payload->child == 0)
                    descriptor->phase = 2;
            }
        }
        break;
    }
    return 0;
}
