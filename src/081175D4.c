#include "control_flags.h"

/* Target: complete [0x081175D4, 0x08117782), 430 bytes including literals. */
typedef struct {
    u16 phase;
} Descriptor081175D4;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation081175D4;

typedef struct {
    u16 delay;
    u8 unknown_02[6];
    void *child;
    Interpolation081175D4 first_motion;
    Interpolation081175D4 second_motion;
    void *first_window;
    void *second_window;
} Payload081175D4;

extern const u8 data_0894D97C[];
extern void func_080E0608(Interpolation081175D4 *, s16, s16, s16);
extern void func_080E064C(Interpolation081175D4 *);
extern u8 func_080E0690(Interpolation081175D4 *);
extern void *func_080DAB84(u8, s16, s16, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080DAC40(void *, s16, s16, u16);
extern void *func_080D9B64(void *);
extern void *func_080D3F08(void *);

u32 func_081175D4(void *task, Descriptor081175D4 *descriptor,
                  Payload081175D4 *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100:
        g_control_flags_03000940.winin_lo = 31;
        g_control_flags_03000940.winin_hi = 63;
        g_control_flags_03000940.winout_lo = 31;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xFF;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 0xFF;
        g_control_flags_03000940.display |= 0x6000;
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
        func_080DAC40(payload->first_window, 120, 52,
                     payload->first_motion.current);
        if (payload->delay != 0) {
            payload->delay--;
            break;
        }
        func_080E064C(&payload->second_motion);
        func_080DAC40(payload->second_window, 120, 52,
                     payload->second_motion.current);
        if (func_080E0690(&payload->first_motion) &&
            func_080E0690(&payload->second_motion)) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.display &= 0x9fff;
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
