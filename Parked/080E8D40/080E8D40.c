#include "ffta.h"

/* Target 0x080E8D40..0x080E8F3C (508 bytes):
 * f0b5474680b484b0071c0d1c161c2b8880204000834228d0834204dc002b0dd0012b1fd0e0e00448834200d18de00130834200d1b0e0d7e001010000e88ab0706c68b46205220006002800d00022044900930197201c0123f7f72efb7062c3e004833908eaf786fdbee0706af7f716fc041c7462002c00d0b6e0b06a0021eff74bfd0006002800d1ace0b06a0021f4f769fb8046311db21d0023f4f7b5fcb06022480421735e0622b15e0091019400210222eef715fa1e48391cebf783fcb0610121ebf7cdfc1b48391cebf747f8f061194b0097002002210022f0f7bffc3062b3791a1c403a1206120e0021f0f70efd12490420009001979624029440460c22a023f4f7cff8f06234800d480097012104220023f6f79aff30634046f4f790fb000600280ed0288801305ce0144f8f08b491940840d79408708339087483390888833908812040004de03088013830800004002848d10421705e0622b15e02220092321c0c320192094a0292039700220123edf7f1f8706106480097012104220023f6f763ff3063288801302be000004083390890833908f069ebf715f8f061002821d102201af75ffb134a118881431180306af0f736fe041c3462002c13d1b069002802d0ebf72ffcb4617069edf711f97061002807d1f06af2f79ffdf062002801d102202880002004b008bc9846f0bc02bc0847000040090003
 */

typedef struct CurveDescriptor {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 selector;
} CurveDescriptor;

typedef struct CurveState {
    u16 timer;
    u8 selector;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *underlying;
    u8 unknown_0C[8];
    void *coordinate_child;
    void *optional_child;
    void *sequence_child;
    void *display_child;
    void *initial_child;
    void *wrapper;
    void *effect_child;
    void *record_child;
} CurveState;

extern u16 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D3F08(void *object);
extern void *func_080D4704(const void *data, void *parent);
extern void func_080D4768(void *object);
extern void func_080D47A0(void *object, u8 enabled);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 flags,
                           void *storage, const void *data, void *parent);
extern void *func_080D6134(void *object);
extern void func_080D7220(const void *data, u8 bank, u8 layer,
                          s16 x, s16 y, u16 flags);
extern u32 func_080D8858(void *wrapper, u16 flags);
extern void *func_080D979C(u8 first, u8 second, u8 third,
                           const void *data, void *parent);
extern void func_080D984C(void *object, u8 pair, u8 first, u8 second);
extern void *func_080D9B64(void *object);
extern void *func_080DBA5C(void *object);
extern void *func_080DCFE4(void *wrapper, const void *data, u8 mode,
                           u16 first, u16 second, void *parent, s16 fallback);
extern void *func_080DD4A4(void *wrapper, u8 index);
extern u32 func_080DD580(void *wrapper);
extern void *func_080DD748(void *wrapper, s16 *x, s16 *y, s16 *z);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                           u16 value, void *parent);
extern void *func_080E03F8(void *wrapper, const void *data, u8 count,
                           u8 selector, const s16 *coordinates, void *parent);
extern void *func_080E05DC(void *object);

u32 func_080E8D40(void *task, void *descriptor, void *payload)
{
    CurveDescriptor *control = descriptor;
    CurveState *state = payload;
    void *selected_wrapper;
    u8 vertical;
    u16 mask;

    switch (control->phase) {
    case 0:
        state->selector = control->selector;
        state->wrapper = control->object;
        state->initial_child = func_080E03F8(state->wrapper,
            (const void *)0x08398304, state->selector ? 0 : 5, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->initial_child = func_080E05DC(state->initial_child);
        if (state->initial_child != 0)
            break;
        if ((u8)func_080D8858(state->wrapper, 0) == 0) {
            control->phase = 2;
            break;
        }
        selected_wrapper = func_080DD4A4(state->wrapper, 0);
        state->underlying = func_080DD748(selected_wrapper,
            &state->x, &state->y, 0);
        func_080D7220((const void *)0x088F4F14, 0, 2,
            state->x, state->y, 0);
        state->optional_child = func_080D4704((const void *)0x089491B4, task);
        func_080D47A0(state->optional_child, 1);
        state->sequence_child = func_080D3E9C((const void *)0x0894D740, task);
        state->display_child = func_080D979C(0, 2, 0,
            (const void *)0x08398370, task);
        vertical = (u8)state->y;
        func_080D984C(state->display_child, 0, (u8)(vertical - 64), vertical);
        state->effect_child = func_080DCFE4(selected_wrapper,
            (const void *)0x08398374, 12, 160, 4, task, 150);
        state->timer = 150;
        state->record_child = func_080DFD8C((const void *)0x08398388,
            1, 4, 0, task);
        if ((u8)func_080DD580(selected_wrapper))
            control->phase++;
        else
            control->phase = 0x102;
        break;
    case 0x101:
        state->timer--;
        if (state->timer == 0) {
            state->coordinate_child = func_080D6098(state->x, state->y,
                0, 1, 2, state->unknown_0C, (const void *)0x08398340, task);
            state->record_child = func_080DFD8C((const void *)0x08398390,
                1, 4, 0, task);
            control->phase++;
        }
        break;
    case 0x102:
        state->sequence_child = func_080D3F08(state->sequence_child);
        if (state->sequence_child != 0)
            break;
        mask = func_080035A8(2);
        *(u16 *)0x03000940 &= ~mask;
        state->display_child = func_080D9B64(state->display_child);
        if (state->display_child != 0)
            break;
        if (state->optional_child != 0) {
            func_080D4768(state->optional_child);
            state->optional_child = 0;
        }
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child != 0)
            break;
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child == 0)
            control->phase = 2;
        break;
    }
    return 0;
}

