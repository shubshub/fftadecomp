#include "ffta.h"

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
} Descriptor08117784;

typedef struct {
    u8 unknown_00[8];
    InterpolationState first;
    InterpolationState second;
} Payload08117784;

extern void func_0801E610(u8 *, u8 *);
extern void func_080D4D58(u8, u8);
extern void func_080D4DA0(u8, u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);

/* Complete [0x08117784, 0x08117884), 256 bytes.
 * Target:
 * f0b581b00f1c151c398880204000814208d081426fdd0130814227d0013081424dd0
 * 68e06c4601346846211c06f72eff684600780121bdf7cdfa20780121bdf7c9fa0020
 * 0021bdf7e9fa281c083000210f221423c8f716ff281c143000210f221423c8f70fff
 * 3888013043e02c1c0834201cc8f729ff2e1c1436301cc8f724ff287a297dbdf7cafa
 * 201cc8f73fff0006002830d0301cc8f739ff000600282ad0201c0f2100221423c8f7
 * ecfe301c0f2100221423c8f7e6fe388801301ae02c1c0834201cc8f700ff2e1c1436
 * 301cc8f7fbfe287a297dbdf7a1fa201cc8f716ff0006002807d0301cc8f710ff0006
 * 002801d002203880002001b0f0bc02bc0847
 */
u32 func_08117784(void *task, Descriptor08117784 *descriptor,
                  Payload08117784 *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100: {
        u8 first, second;

        func_0801E610(&first, &second);
        func_080D4D58(first, 1);
        func_080D4D58(second, 1);
        func_080D4DA0(0, 0);
        func_080E0608(&payload->first, 0, 15, 20);
        func_080E0608(&payload->second, 0, 15, 20);
        descriptor->phase++;
        break;
    }
    case 0x101:
        func_080E064C(&payload->first);
        func_080E064C(&payload->second);
        func_080D4DA0((u8)payload->first.current,
                      (u8)payload->second.current);
        if (func_080E0690(&payload->first) &&
            func_080E0690(&payload->second)) {
            func_080E0608(&payload->first, 15, 0, 20);
            func_080E0608(&payload->second, 15, 0, 20);
            descriptor->phase++;
        }
        break;
    case 0x102:
        func_080E064C(&payload->first);
        func_080E064C(&payload->second);
        func_080D4DA0((u8)payload->first.current,
                      (u8)payload->second.current);
        if (func_080E0690(&payload->first) &&
            func_080E0690(&payload->second))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
