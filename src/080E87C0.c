#include "ffta.h"
#include "control_flags.h"
/* Target: 0x080E87C0..0x080E8A30 (624 bytes). */
typedef struct { u16 state, unknown_2; void *object; u32 unknown_8[3]; s16 kind; u16 variant; } Event;
typedef struct { u8 kind, variant, count, index, delay, special, ready, unknown_7; void *child, *effect, *object; u32 tasks[2]; void *intro; } State;
typedef struct { u32 unknown_0; void *object; u32 unknown_8[3]; u16 kind, index; u32 unknown_18; } Descriptor;
extern u8 data_08398108[], data_083981E4[], data_08398200[], data_088F46CC[];
extern void *data_083980FC[];
extern void func_080E8590(void);
extern void *func_080E03F8(void *, void *, unsigned, unsigned, unsigned, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D7220(void *, unsigned, unsigned, unsigned, unsigned, unsigned);
extern unsigned func_080035D0(unsigned);
extern unsigned func_080035A8(unsigned);
extern u8 func_080D3B54(void *);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, unsigned);
extern u8 func_080E0570(u32 *, unsigned);
extern u8 func_080DE1F0(void *);
extern void *func_080DDF68(void *, void **, unsigned, unsigned, u8 *, void *, unsigned, unsigned, void *);
extern void func_080D8CD4(void *);
extern void *func_080DD4A4(void *, unsigned);
extern u32 func_08005B6C(void *callback, unsigned, Descriptor *, void *);
int func_080E87C0(void *owner, Event *event, State *state)
{
    Descriptor descriptor;
    unsigned mode, speed;
    void *object;
    u32 *tasks;
    u8 slot;
    switch (event->state) {
    case 0:
        if (event->kind != 233) {
            state->kind = event->kind - 30;
            state->special = 0;
            mode = 1;
        } else {
            state->kind = 0;
            state->special = 1;
            mode = 0;
        }
        state->variant = event->variant;
        object = event->object;
        state->object = object;
        speed = data_08398108[state->kind];
        if (state->variant) speed = 0;
        state->intro = func_080E03F8(object, data_083980FC[state->kind], speed, mode, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->intro = func_080E05DC(state->intro);
        if (state->intro) break;
        func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
        g_control_flags_03000940.winout_lo = 63 & ~func_080035D0(3);
        g_control_flags_03000940.winout_hi = 63;
        g_control_flags_03000940.display |= 0x8000;
        if (state->special) {
            if (func_080D3B54(state->object)) goto finish;
            state->effect = func_080DDF68(state->object, &state->child, 0x8007, 2, &state->ready, data_08398200, 5, 0, owner);
            event->state++;
        } else event->state = 0x103;
        break;
    case 0x101:
        if (!state->ready) break;
        func_080D8CD4(state->object);
        state->index = 4;
        event->state++;
        break;
    case 0x102:
        if (state->index && --state->index) break;
        if (func_080D8B4C()) break;
        event->state++;
        break;
    case 0x103:
        state->count = func_080D8858(state->object, 0);
        if (!state->count) goto finish;
        state->delay = 1;
        event->state++;
        break;
    case 0x104:
        tasks = state->tasks;
        func_080E0570(tasks, 2);
        if (--state->delay) break;
        slot = tasks[0] != 0;
        descriptor.kind = state->kind;
        descriptor.index = state->index;
        descriptor.object = func_080DD4A4(state->object, state->index);
        state->tasks[slot] = func_08005B6C(func_080E8590, 0x34, &descriptor, owner);
        state->delay = data_083981E4[state->kind];
        state->index++;
        if (state->index == state->count) event->state++;
        break;
    case 0x105:
        if (state->special && !func_080DE1F0(state->child)) break;
        if (!func_080E0570(state->tasks, 2)) break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        g_control_flags_03000940.display &= 0x7fff;
finish:
        event->state = 2;
        break;
    }
    return 0;
}
