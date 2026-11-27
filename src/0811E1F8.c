// Target: complete [0x0811E1F8, 0x0811E618), 1056 bytes, 528 instructions.
#include "control_flags.h"

typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    s16 value;
} Event;

/* One WIN0H scanline entry, as declared by sibling src/0811435C.c; every
 * byte store is preceded by a load of the same byte (0x0811E542-0x0811E548). */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

typedef struct {
    u16 timer;
    u8 mode;
    u8 index;
    s16 x;
    s16 y;
    void *window_a;
    void *window_b;
    s16 offsets[160];
    u8 delays[160];
    void *sequence;
    void *effect;
} Context;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
    s16 unknown_08[2];
} Region;


extern const u8 data_08149FB4[];
extern const Region data_08149FB8;
extern const s16 data_083A7314[][5];
extern const u8 data_083A7328[];
extern const u8 data_083A732C[];

extern u16 func_080035D0(u8);
extern void func_0801B798(const Region *, u8);
extern void func_0801B878(void);
extern void func_0801E58C(s16, s16);
extern void func_0801E610(u8 *, u8 *);
extern void func_0801E6F0(s16 *, s16 *);
extern void func_080D35D8(void);
extern void func_080D3AC0(u8);
extern void *func_080D3EC0(const void *, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D993C(u8, u8, u8, void *);
extern s16 *func_080D997C(void *, u8);
extern void *func_080D9B64(void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080DAB84(u8, u8, u8, void *);
extern WindowLine *func_080DABB4(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern void func_0814186C(const void *, void *, u32);
extern void *func_081443FC(void *, const void *, u32);

u32 func_0811E1F8(void *owner, Event *event, Context *context)
{

    switch (event->state) {
    case 0:
        switch (event->value) {
        case 0x18D:
        case 0x18E:
        case 0x18F:
        case 0x190:
        case 0x191:
            context->mode = 0;
            context->index = event->value - 0x18D;
            func_080D3AC0(0);
            break;
        case 0x194:
        case 0x195:
        case 0x196:
            context->mode = 1;
            context->index = event->value - 0x194;
            break;
        }
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        func_0801E6F0(&context->x, &context->y);
        {
            /* CpuFill16 source, as in sibling src/0811E034.c: the ROM takes
             * &fill twice (0x0811E292, 0x0811E29E). */
            volatile u16 fill = context->x;
            func_0814186C((const void *)&fill, context->offsets, 0x010000A0);
        }
        func_0801E58C(0, context->y >> 3);
        event->state++;
        break;
    case 0x101:
    {
        InterpolationState motion;
        u8 heights[2];
        u8 first;
        u8 second;
        u8 i;

        func_081443FC(heights, data_08149FB4, sizeof(heights));
        func_0801E610(&first, &second);
        context->window_a = func_080D993C(second > first ? first : second, 0, 2, owner);
        if (context->mode == 0)
            context->window_b = func_080DAB84(0, 0, 0, owner);
        else
            context->window_b = func_080DAB84(0, 0, 240, owner);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 160;
        g_control_flags_03000940.winin_lo = 0x3F & ~(func_080035D0(first) | func_080035D0(second));
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.display |= 0x2000;
        func_080D9BA8(context->window_a, 1);
        func_080D9BA8(context->window_b, 1);
        if (context->mode == 1) {
            s16 *lower = func_080D997C(context->window_a, 0);
            s16 *upper = func_080D997C(context->window_a, 2);

            for (i = 0; i < 160; i++) {
                if (i & 1) {
                    context->offsets[i] -= 660;
                    lower[i] -= 660;
                    upper[i] -= 660;
                } else {
                    context->offsets[i] += 660;
                    lower[i] += 660;
                    upper[i] += 660;
                }
            }
        }
        context->sequence = func_080D3EC0(data_083A7314[context->mode],
                                          data_083A7328[context->mode], owner);
        func_080E0608(&motion, 40, 0, 80);
        for (i = 0; i < 80; i++) {
            context->delays[i] = motion.current;
            context->delays[159 - i] = motion.current;
            func_080E064C(&motion);
        }
        context->effect = func_080DFD8C(data_083A732C, 1, 4, heights[context->mode], owner);
        context->timer = 150;
        event->state++;
        break;
    }
    case 0x102:
    {
        s16 *lower = func_080D997C(context->window_a, 0);
        s16 *upper = func_080D997C(context->window_a, 2);
        WindowLine *lines = func_080DABB4(context->window_b);
        /* 0x200 is built once before the loop (0x0811E494) and subtracted
         * as a register (0x0811E51C). */
        s16 wrap = 512;
        u8 i;

        for (i = 0; i < 160; i++) {
            s16 edge;
            u8 left;
            u8 right;

            if (context->delays[i] != 0) {
                context->delays[i]--;
            } else if (context->mode == 0 || context->offsets[i] != context->x) {
                if (i & 1) {
                    lower[i] += 6;
                    upper[i] += 6;
                    context->offsets[i] += 6;
                } else {
                    lower[i] -= 6;
                    upper[i] -= 6;
                    context->offsets[i] -= 6;
                }
                edge = context->offsets[i] + 240;
                edge -= wrap;
                if (edge > 0) {
                    right = 240;
                    if (edge > 239)
                        left = 0;
                    else
                        left = 240 - edge;
                    lines[i].left = left;
                    lines[i].right = right;
                }
                /* Sign-extending reload, then negate: ldrsh/rsbs at 0x0811E54E. */
                edge = context->offsets[i];
                edge = -edge;
                if (edge > 0) {
                    left = 0;
                    if (edge > 239)
                        right = 240;
                    else
                        right = edge;
                    lines[i].left = left;
                    lines[i].right = right;
                }
            } else {
                lines[i].left = 0;
                lines[i].right = 0;
            }
        }
        if (--context->timer == 0) {
            g_control_flags_03000940.display &= ~0x2000;
            event->state++;
        }
        break;
    }
    case 0x103:
        context->sequence = func_080D3F08(context->sequence);
        if (context->sequence == 0) {
            context->window_a = func_080D9B64(context->window_a);
            if (context->window_a == 0) {
                context->window_b = func_080D9B64(context->window_b);
                if (context->window_b == 0) {
                    if (context->mode == 0 && context->index == 3) {
                        Region region = data_08149FB8;

                        func_0801B798(&region, 0);
                    }
                    func_0801B878();
                    event->state = 2;
                }
            }
        }
        break;
    }
    return 0;
}
