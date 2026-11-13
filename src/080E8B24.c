#include "ffta.h"
#include "control_flags.h"

// Target: 0x080E8B24..0x080E8D3E (538 bytes).

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[4];
    u32 flags;
    u8 unknown_10[6];
    u16 selector;
} Control080E8B24;

typedef struct {
    u8 selector;
    u8 count;
    u8 index;
    u8 delay;
    u32 tasks[2];
    void *display;
    void *sequence;
    void *effects[3];
    void *overlay;
    void *initial;
    void *wrapper;
    void *record;
} State080E8B24;

typedef struct {
    u32 unknown_00;
    void *object;
    u32 unknown_08[3];
    u16 index;
    u16 unknown_16;
    u32 unknown_18;
} Descriptor080E8B24;

extern u32 func_080E8A30(void *task, void *descriptor, void *work);
extern void *func_080E03F8(void *wrapper, const void *data, u8 count,
                           u8 selector, const s16 *coordinates, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *object);
extern u8 func_080D8924(void *wrapper, u32 first, u32 second, void *parent);
extern void func_080D49FC(u8 first, u8 second, u16 third, s16 x, s16 y);
extern void *func_080D4B64(u8 group, const void *data, u16 value, u8 mode);
extern u16 func_080035A8(u8 index);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags,
                           u16 value, void *parent);
extern u8 func_080E0570(u32 *tasks, u32 count);
extern void *func_080DD4A4(void *wrapper, u8 index);
extern u32 func_08005B6C(void *callback, u16 size, void *descriptor,
                         void *parent);
extern void *func_080D3F08(void *object);
extern void *func_080D4D2C(void *display, u8 mode);
extern u8 func_080D48DC(void **tasks, u16 count);
extern void *func_080D4774(void *object);

extern const u8 data_08398264[];
extern const u8 data_083982B4[];
extern const u8 data_088EDF80[];
extern const u8 data_08949784[];
extern const u8 data_08949798[];
extern const u8 data_089497AC[];
extern const u8 data_0894AB00[];
extern const u8 data_0894D7E4[];

u32 func_080E8B24(void *task, Control080E8B24 *control,
                  State080E8B24 *state)
{
    Descriptor080E8B24 descriptor;
    u8 kind;
    u8 slot;

    switch (control->phase) {
    case 0:
        state->selector = control->selector;
        state->wrapper = control->object;
        kind = 3;
        if (state->selector)
            kind = 0;
        if (control->flags & 1)
            kind = 0;
        state->initial = func_080E03F8(state->wrapper,
            data_08398264, kind, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->initial = func_080E05DC(state->initial);
        if (state->initial)
            break;
        if (state->selector) {
            state->delay = 1;
            state->count = func_080D8924(state->wrapper, 0, 60, task);
            if (!state->count)
                control->phase = 0x102;
            else
                control->phase = 0x101;
            break;
        }
        func_080D49FC(0, 2, 0, 120, 96);
        state->display = func_080D4B64(0, data_088EDF80, 0x3C7, 6);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->sequence = func_080D3E9C(data_0894D7E4, task);
        state->effects[0] = func_080D4704(data_08949784, task);
        state->effects[1] = func_080D4704(data_08949798, task);
        state->effects[2] = func_080D4704(data_089497AC, task);
        state->overlay = func_080D4704(data_0894AB00, task);
        state->delay = 40;
        state->count = func_080D8924(state->wrapper, 0, 60, task);
        state->record = func_080DFD8C(data_083982B4, 1, 4, 0, task);
        if (!state->count)
            control->phase = 0x102;
        else
            control->phase++;
        break;
    case 0x101:
        func_080E0570(state->tasks, 2);
        if (--state->delay)
            break;
        slot = state->tasks[0] != 0;
        descriptor.index = state->index;
        descriptor.object = func_080DD4A4(state->wrapper, state->index);
        state->tasks[slot] = func_08005B6C(func_080E8A30, 0x20, &descriptor,
                                           task);
        state->delay = 45;
        state->index++;
        if (state->index == state->count)
            control->phase++;
        break;
    case 0x102:
        state->sequence = func_080D3F08(state->sequence);
        if (state->sequence)
            break;
        state->display = func_080D4D2C(state->display, 0);
        if (state->display)
            break;
        if (!func_080D48DC(state->effects, 3))
            break;
        state->overlay = func_080D4774(state->overlay);
        if (state->overlay)
            break;
        if (func_080E0570(state->tasks, 2))
            control->phase = 2;
        break;
    }
    return 0;
}
