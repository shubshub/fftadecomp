#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    u32 input;
} Descriptor080F15C8;

typedef struct {
    s16 x, y;
    u8 delay;
    u8 unknown_05[3];
    void *timeline;
    void *first_child;
    void *second_child;
    void *drawing;
    u32 input;
    void *record;
} Payload080F15C8;

extern const u8 data_0894D97C[], data_0894B504[], data_0894B268[], data_0839A56C[];
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DAD94(s16, s16, u8, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080DAE44(void *);

/* Complete target [0x080F15C8, 0x080F173A): 370 bytes. */
u32 func_080F15C8(void *task, Descriptor080F15C8 *descriptor,
                  Payload080F15C8 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->input = descriptor->input;
        payload->x = 104;
        payload->y = 40;
        break;
    case 0x100:
        payload->timeline = func_080D3E9C(data_0894D97C, task);
        payload->drawing = func_080DAD94(payload->x, payload->y, 1, task);
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winin_hi = 0x3f;
        g_control_flags_03000940.winout_lo = 0x1f;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 0xff;
        g_control_flags_03000940.display |= 0x6000;
        payload->first_child = func_080D4704(data_0894B504, task);
        payload->second_child = func_080D4704(data_0894B268, task);
        payload->record = func_080DFD8C(data_0839A56C, 1, 4, 0, task);
        payload->delay = 28;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->delay) {
            if (--payload->delay)
                break;
            g_control_flags_03000940.display &= 0x9fff;
            g_control_flags_03000940.bldcnt_lo = 0;
        }
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline) break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child) break;
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child) break;
        payload->drawing = func_080DAE44(payload->drawing);
        if (payload->drawing) break;
        descriptor->phase++;
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
