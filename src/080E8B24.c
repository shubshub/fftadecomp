#include "ffta.h"

/* Target: 0x080E8B24..0x080E8D3E, 538 complete bytes, 221 instructions.
 * Offset views describe reached accesses; original object types are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[4];
    u16 index;
    u16 variant;
    u32 unknown_18;
} EffectRequest;

typedef struct {
    u8 variant;
    u8 count;
    u8 index;
    u8 delay;
    void *children[2];
    void *effect;
    void *animation;
    void *overlays[3];
    void *last_overlay;
    void *transition;
    void *object;
    void *controller;
} EffectState;

extern const u8 data_08398264[];
extern const u8 data_088EDF80[];
extern const u8 data_0894D7E4[];
extern const u8 data_08949784[];
extern const u8 data_08949798[];
extern const u8 data_089497AC[];
extern const u8 data_0894AB00[];
extern const u8 data_083982B4[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8924(void *, u32, u32, void *);
extern void func_080D49FC(u32, u32, u32, s16, s16);
extern void *func_080D4B64(u32, const void *, u32, u32);
extern u32 func_080035A8(u32);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u32, u32, u32, void *);
extern u8 func_080E0570(void **, u32);
extern void *func_080DD4A4(void *, u32);
extern u32 func_080E8A30(void *, EffectRequest *, void *);
extern void *func_08005B6C(u32 (*)(void *, EffectRequest *, void *), u16,
                          EffectRequest *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u32);
extern u8 func_080D48DC(void **, u32);
extern void *func_080D4774(void *);

u32 func_080E8B24(void *task, EffectRequest *request, EffectState *state)
{
    EffectRequest child;
    u32 mode;
    u8 slot;
    u32 mask;
    u16 *control_flags;
    u32 flags;

    switch (request->phase) {
    case 0:
        state->variant = request->variant;
        state->object = request->object;
        mode = 3;
        if (state->variant)
            mode = 0;
        if (request->flags & 1)
            mode = 0;
        state->transition = func_080E03F8(state->object, data_08398264,
                                         mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->transition = func_080E05DC(state->transition);
        if (state->transition)
            break;
        if (state->variant) {
            state->delay = 1;
            state->count = func_080D8924(state->object, 0, 60, task);
            if (!state->count)
                request->phase = 0x102;
            else
                request->phase = 0x101;
            break;
        }
        func_080D49FC(0, 2, 0, 120, 96);
        state->effect = func_080D4B64(0, data_088EDF80, 0x3C7, 6);
        mask = func_080035A8(2);
        control_flags = &g_control_flags_03000940;
        flags = *control_flags;
        *control_flags = flags | mask;
        state->animation = func_080D3E9C(data_0894D7E4, task);
        state->overlays[0] = func_080D4704(data_08949784, task);
        state->overlays[1] = func_080D4704(data_08949798, task);
        state->overlays[2] = func_080D4704(data_089497AC, task);
        state->last_overlay = func_080D4704(data_0894AB00, task);
        state->delay = 40;
        state->count = func_080D8924(state->object, 0, 60, task);
        state->controller = func_080DFD8C(data_083982B4, 1, 4, 0, task);
        if (!state->count)
            request->phase = 0x102;
        else
            request->phase++;
        break;
    case 0x101:
        func_080E0570(state->children, 2);
        state->delay--;
        if (state->delay)
            break;
        slot = state->children[0] != 0;
        child.index = state->index;
        child.object = func_080DD4A4(state->object, state->index);
        state->children[slot] = func_08005B6C(func_080E8A30, 32, &child, task);
        state->delay = 45;
        state->index++;
        if (state->index == state->count)
            request->phase++;
        break;
    case 0x102:
        state->animation = func_080D3F08(state->animation);
        if (state->animation)
            break;
        state->effect = func_080D4D2C(state->effect, 0);
        if (state->effect)
            break;
        if (!func_080D48DC(state->overlays, 3))
            break;
        state->last_overlay = func_080D4774(state->last_overlay);
        if (state->last_overlay)
            break;
        if (func_080E0570(state->children, 2))
            request->phase = 2;
        break;
    }
    return 0;
}
