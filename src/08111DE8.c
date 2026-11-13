// Target: complete [0x08111DE8, 0x08111F60), 376 bytes.
#include "control_flags.h"

typedef struct {
    s16 current, remaining, error, step, period, distance;
} InterpolationState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
} Descriptor;

typedef struct {
    void *first;
    void *second;
} ObjectPair;

typedef struct {
    u16 counter;
    u8 unknown_02[6];
    InterpolationState motion_08;
    InterpolationState motion_14;
    InterpolationState motion_20;
    InterpolationState motion_2C;
    void *task;
    ObjectPair *pair;
} Payload;

extern const u8 data_0894DBB0[];
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *task);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080DADFC(void *);
extern void func_080DAC80(void *, s16, s16, u16, u16);

u32 func_08111DE8(void *parent, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->pair = descriptor->object;
        g_control_flags_03000940.winin_lo = 0x1F;
        g_control_flags_03000940.winin_hi = 0x3F;
        g_control_flags_03000940.winout_lo = 0x1F;
        g_control_flags_03000940.display |= 0x6000;
        payload->task = func_080D3E9C(data_0894DBB0, parent);
        func_080E0608(&payload->motion_08, 0x7C, 0x7C, 0x27);
        func_080E0608(&payload->motion_20, 4, 0x78, 0x27);
        payload->counter = 8;
        func_080E0608(&payload->motion_14, 0x7C, 0x7F, 0x23);
        func_080E0608(&payload->motion_2C, 4, 0x78, 0x23);
        break;
    case 1:
        break;
    case 0x100:
        if (payload->counter != 0)
            payload->counter--;
        func_080DADFC(payload->pair->first);
        if (payload->counter == 0)
            func_080DADFC(payload->pair->second);
        func_080DAC80(payload->pair->first, 0x78, payload->motion_08.current,
                      payload->motion_20.current,
                      (u16)(payload->motion_20.current >> 2));
        if (payload->counter == 0)
            func_080DAC80(payload->pair->second, 0x78, payload->motion_14.current,
                          payload->motion_2C.current,
                          (u16)(payload->motion_2C.current >> 2));
        func_080E064C(&payload->motion_08);
        func_080E064C(&payload->motion_20);
        if (payload->counter == 0) {
            func_080E064C(&payload->motion_14);
            func_080E064C(&payload->motion_2C);
        }
        payload->task = func_080D3F08(payload->task);
        if (payload->task == 0 && func_080E0690(&payload->motion_20) &&
            func_080E0690(&payload->motion_2C)) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.display &= 0x9FFF;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
