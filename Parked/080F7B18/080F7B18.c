#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 variant;
} Event;

typedef struct {
    u8 variant;
    u8 delay;
    u8 unknown_02;
    u8 count;
    u16 counter;
    u8 special;
    u8 unknown_07;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_0D[3];
    void *children[5];
    void *object;
    void *unit;
    void *animation;
    void *coordinate_output;
    void *coordinate_task;
    void *sprite;
    void *blend_task;
    void *layer_task;
    u8 unknown_44[4];
    void *setup_task;
    void *record_task;
} State;
typedef struct {
    u32 unknown_00;
    void *unit;
    u8 unknown_08[12];
    u16 index;
    u16 special;
    u32 unknown_18;
} Child;

extern const u8 data_0839BD08[], data_088EA7F0[], data_088EA81C[], data_088EAB24[];
extern const u8 data_0839BDB4[], data_0839BD74[], data_0839BDBC[], data_0839BDB8[];
extern const u8 data_088EF44C[], data_0894D91C[], data_0894ABF0[], data_0894AC40[];
extern const u8 data_0839BDC4[];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern u8 func_080DD494(void *);
extern void *func_080DD47C(void *);
extern u16 func_080DD708(void *);
extern void *func_080DDF68(void *, void **, u32, u32, u8 *, const void *, u32, u32, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u32, u8 *, const void *, u16, u16, void *);
extern void func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern void func_080D8C58(void *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern u8 func_080D8924(void *, u16, u16, void *);
extern u8 func_080E0570(void **, u8);
extern void *func_080DD4A4(void *, u8);
typedef u32 (*Callback)(void *task, void *descriptor, void *state);
extern u32 func_080F7A34(void *, void *, void *);
extern void *func_08005B6C(Callback, u16, void *, void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u8 func_080DE1F0(void *);

u32 func_080F7B18(void *task, Event *event, State *state)
{
    switch (event->phase) {
    case 0: {
        u8 animation;
        state->special = 0;
        if (event->kind == 327)
            state->special = 1;
        state->variant = event->variant;
        state->object = event->object;
        animation = 5;
        if (state->variant)
            animation = 0;
        state->animation = func_080E03F8(state->object, data_0839BD08, animation, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u16 setup;
        state->animation = func_080E05DC(state->animation);
        if (state->animation)
            break;
        if (state->special == 1) {
            func_080D45D0(data_088EA7F0, 6, 1, 6, 1);
            func_080D45D0(data_088EA81C, 7, 1, 1, 1);
            func_080D45D0(data_088EA7F0, 8, 1, 6, 1);
            func_080D45D0(data_088EAB24, 6, 0, 2, 1);
        }
        if (state->variant) {
            state->count = func_080DD494(state->object);
            state->delay = 1;
            event->phase = 0x105;
            break;
        }
        setup = 0x90;
        if (state->special == 1) {
            u16 id = func_080DD708(func_080DD47C(state->object));
            if (id == 0x61)
                setup = 0x54;
            else if (id == 0x65)
                setup = 0x58;
        }
        state->setup_task = func_080DDF68(state->object, &state->unit, setup, 1,
                                         &state->ready, data_0839BDB4, 0, 0, task);
        func_080DBDC8(state->unit, &state->x, &state->y);
        event->phase++;
        break;
    }
    case 0x101:
        if (!state->ready)
            break;
        state->coordinate_task = func_080D6098(state->x, state->y, 0, 1, 1,
                                          &state->coordinate_output, data_0839BD74, task);
        state->record_task = func_080DFD8C(data_0839BDBC, 1, 4, 0, task);
        event->phase++;
        break;
    case 0x102:
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task)
            break;
        func_080DE3BC(state->unit, 0);
        func_080DBA50(state->setup_task);
        state->setup_task = func_080DE4F4(state->unit, 1, &state->ready, data_0839BDB8, 0, 0, task);
        event->phase++;
        break;
    case 0x103:
        if (state->ready) {
            func_080D8CD4(state->object);
            state->counter = 4;
            event->phase++;
        }
        break;
    case 0x104: {
        s16 x, y;
        u32 mask;
        if (state->counter && --state->counter)
            break;
        if (func_080D8B4C())
            break;
        func_080D8C58(state->object, &x, &y);
        func_080D49FC(0, 2, 0, x, y);
        state->sprite = func_080D4B64(0, data_088EF44C, 0x39D, 6);
        mask = func_080035A8(2);
        {
            u16 flags = g_control_flags_03000940.display;
            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        state->blend_task = func_080D3E9C(data_0894D91C, task);
        if (!state->special)
            state->layer_task = func_080D4704(data_0894ABF0, task);
        else
            state->layer_task = func_080D4704(data_0894AC40, task);
        state->record_task = func_080DFD8C(data_0839BDC4, 1, 4, 0, task);
        state->count = func_080D8924(state->object, 0, 40, task);
        if (!state->count) {
            event->phase = 0x106;
            break;
        }
        state->delay = 20;
        event->phase++;
        break;
    }
    case 0x105: {
        Child child;
        func_080E0570(state->children, 5);
        if (--state->delay)
            break;
        child.index = state->counter;
        child.special = state->special;
        child.unit = func_080DD4A4(state->object, state->counter);
        state->children[state->counter] = func_08005B6C(func_080F7A34, 36, &child, task);
        state->delay = 40;
        if (++state->counter == state->count)
            event->phase++;
        break;
    }
    case 0x106:
        if (!func_080E0570(state->children, 5))
            break;
        state->sprite = func_080D4D2C(state->sprite, 0);
        if (state->sprite)
            break;
        state->blend_task = func_080D3F08(state->blend_task);
        if (state->blend_task)
            break;
        state->layer_task = func_080D4774(state->layer_task);
        if (state->layer_task)
            break;
        if (func_080DE1F0(state->unit))
            event->phase = 2;
        break;
    }
    return 0;
}
