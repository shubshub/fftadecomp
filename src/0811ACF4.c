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
} Descriptor0811ACF4;

typedef struct {
    u16 countdown;
    u8 unknown_02[6];
    InterpolationState first;
    InterpolationState second;
} Payload0811ACF4;

extern void func_0801E610(u8 *, u8 *);
extern void func_080D4D58(u8, u8);
extern void func_080D4DA0(u8, u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);

/* Complete [0x0811ACF4, 0x0811AE00), 268 bytes.
 * Target:
 * f0b581b00f1c151c398880204000814208d0814275dd013081422dd001308142
 * 53d06ee02888002802d00138288068e06c4601346846211c03f770fc68460078
 * 0121baf70ff820780121baf70bf800200021baf72bf8281c083000210f221423
 * c5f758fc281c143000210f221423c5f751fc3888013043e02c1c0834201cc5f7
 * 6bfc2e1c1436301cc5f766fc287a297dbaf70cf8201cc5f781fc0006002830d0
 * 301cc5f77bfc000600282ad0201c0f2100221423c5f72efc301c0f2100221423
 * c5f728fc388801301ae02c1c0834201cc5f742fc2e1c1436301cc5f73dfc287a
 * 297db9f7e3ff201cc5f758fc0006002807d0301cc5f752fc0006002801d00220
 * 3880002001b0f0bc02bc0847
 */
u32 func_0811ACF4(void *task, Descriptor0811ACF4 *descriptor,
                  Payload0811ACF4 *payload)
{
    switch (descriptor->phase) {
    case 0:
    case 1:
        break;
    case 0x100: {
        u8 first, second;

        if (payload->countdown != 0) {
            payload->countdown--;
            break;
        }
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
