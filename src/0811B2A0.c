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
    u8 unknown_00[8];
    void *child;
    void *window;
    struct InterpolationState motion;
    void *record_task;
};

extern const u8 data_088EB4A4[];
extern const u8 data_083A6A08[];
extern u16 g_control_flags_03000940;
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D35D8(void);
extern void *func_0811ECD0(u8, void *);
extern void *func_0811ED14(void *);
extern void *func_0811EC30(void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E064C(struct InterpolationState *);
extern void func_080DAC40(void *, s16, s16, u16);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080D8D78(void);
extern u32 func_080035A8(u8);
extern void *func_080D9B64(void *);

/* Target: complete [0x0811B2A0, 0x0811B3AE), 270 bytes, 111 instructions. */
u32 func_0811B2A0(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        func_080D45D0(data_088EB4A4, 6, 0, 0, 1);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->child = func_0811ECD0(1, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->child = func_0811ED14(payload->child);
        if (payload->child == 0) {
            payload->window = func_0811EC30(task);
            func_080E0608(&payload->motion, 0, 145, 60);
            payload->record_task = func_080DFD8C(data_083A6A08, 1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        func_080E064C(&payload->motion);
        func_080DAC40(payload->window, 120, 80, payload->motion.current);
        if (func_080E0690(&payload->motion)) {
            u32 mask;

            func_080D8D78();
            mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
            g_control_flags_03000940 &= ~func_080035A8(3);
            g_control_flags_03000940 &= 0xdfff;
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->window = func_080D9B64(payload->window);
        if (payload->window == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
