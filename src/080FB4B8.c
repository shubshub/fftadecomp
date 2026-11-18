#include "ffta.h"
#include "effect_task.h"

typedef struct FB4B8Request {
    u16 phase;
    u16 unknown_02;
    void *unit;
    u8 unknown_08[14];
    u16 mode;
} FB4B8Request;

typedef struct FB4B8State {
    s16 x;
    s16 y;
    u8 mode;
    u8 ready;
    u8 unknown_06[2];
    void *object;
    void *selected;
    void *unit;
    void *initial;
    u8 coordinates[12];
    void *motion;
    void *graphics;
    void *overlay;
    void *fade;
    void *action;
    void *transition;
    void *animation;
} FB4B8State;

extern const u8 data_0839CCD0[];
extern const u8 data_0839CD00[];
extern const u8 data_0839CD78[];
extern const u8 data_0839CD74[];
extern const u8 data_0839CD18[];
extern const u8 data_0839CD60[];
extern const u8 data_0839CD80[];
extern const u8 data_088EF398[];
extern const u8 data_0894D90C[];
extern const u8 data_0894AAB0[];
extern u16 g_control_flags_03000940;

u32 func_080035A8(u8 layer);
void func_080D38B4(void);
u8 func_080D3B54(void *unit);
void *func_080D3E9C(const void *resource, void *parent);
void *func_080D3F08(void *handle);
void *func_080D4724(const void *resource, void *parent, u16 delay);
void *func_080D4774(void *handle);
void func_080D49FC(u8 first, u8 second, u16 flags, s16 x, s16 y);
void *func_080D4B64(u8 layer, const void *resource, u16 flags, u8 bank);
void *func_080D4D2C(void *handle, u8 layer);
void *func_080D6098(s16 x, s16 y, s16 z, u8 flags, u16 mode,
                   void *coordinates, const void *resource, void *parent);
void *func_080D6134(void *handle);
u8 func_080D8858(void *unit, u16 flags);
u8 func_080D8B4C(void);
void *func_080DBA5C(void *handle);
void func_080DBDC8(void *object, s16 *x, s16 *y);
u8 func_080DBFFC(void *unit, u8 index);

void *func_080DD47C(void *unit);
void *func_080DD4A4(void *unit, u8 index);
void *func_080DD748(void *object, s16 *x, s16 *y, u32 flags);
void *func_080DDF68(void *unit, void **object, u16 flags, u8 mode,
                   u8 *signals, const void *resource, u16 option,
                   u16 argument, void *parent);
void func_080DE10C(void *object, u16 mode);
u8 func_080DE1F0(void *object);
void *func_080DFD8C(const void *resource, u8 mode, u16 flags,
                   u16 argument, void *parent);
void *func_080E03F8(void *unit, const void *resource, u8 flags, u8 mode,
                   const s16 *coordinates, void *parent);
void *func_080E05DC(void *handle);

/* Complete physical target: 674 bytes. Local declarations are conditional
 * incoming-bit transport views grounded in the root and saved full entries.
 * Unknown bytes and callback-mutated fields require storage/access compatibility;
 * these views assert no initialization, bounds, nonalias or helper effects.
 */
s32 func_080FB4B8(void *parent, FB4B8Request *request, FB4B8State *state)
{
    s16 x, y;
    void *object;
    u8 flags;

    switch (request->phase) {
    case 0:
        state->mode = request->mode;
        object = request->unit;
        state->unit = object;
        flags = 4;
        if (state->mode)
            flags = 0;
        state->initial = func_080E03F8(object, data_0839CCD0, flags, 0,
                                      0, parent);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u32 mask;
        u16 control;
        state->initial = func_080E05DC(state->initial);
        if (!state->initial) {
            if (func_080D3B54(state->unit)) {
                request->phase = 2;
            } else {
                state->object = func_080DD47C(state->unit);
                func_080DE10C(state->object, 0x24);
                func_080DBDC8(state->object, &x, &y);
                func_080D49FC(0, 2, 0, x, y);
                state->graphics = func_080D4B64(0, data_088EF398, 0x3BF, 6);
                mask = func_080035A8(2);
                control = g_control_flags_03000940;
                control |= mask;
                g_control_flags_03000940 = control;
                state->overlay = func_080D3E9C(data_0894D90C, parent);
                state->motion = func_080D6098(x, y, 0, 1, 1,
                    state->coordinates, data_0839CD00, parent);
                state->fade = func_080D4724(data_0894AAB0, parent, 15);
                state->animation = func_080DFD8C(data_0839CD78, 1, 4, 0, parent);
                ++request->phase;
            }
        }
        break;
    }
    case 0x101: {
        u32 mask;
        state->graphics = func_080D4D2C(state->graphics, 0);
        if (state->graphics)
            break;
        state->overlay = func_080D3F08(state->overlay);
        if (state->overlay)
            break;
        state->fade = func_080D4774(state->fade);
        if (state->fade)
            break;
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        state->motion = func_080D6134(state->motion);
        if (state->motion)
            break;
        state->transition = func_080DDF68(state->unit, 0, 0x8007, 1,
            &state->ready, data_0839CD74, 5, 0, parent);
        ++request->phase;
        break;
    }
    case 0x102:
        if (!state->ready)
            break;
        func_080DBFFC(state->unit, 0);
        ++request->phase;
        /* fall through */
    case 0x103:
        if (func_080D8B4C())
            break;
        if (!func_080D8858(state->unit, 0)) {
            request->phase = 2;
        } else {
            object = func_080DD4A4(state->unit, 0);
            state->selected = func_080DD748(object, &state->x, &state->y, 0);
            state->motion = func_080D6098(state->x, state->y, 0, 1, 3,
                state->coordinates, data_0839CD18, parent);
            state->action = func_080DCFE4(object, data_0839CD60, 12,
                                         0x26, 4, parent, 0x26);
            state->animation = func_080DFD8C(data_0839CD80, 3, 4, 0, parent);
            ++request->phase;
        }
        break;
    case 0x104:
        if (!func_080DE1F0(state->object))
            break;
        state->motion = func_080D6134(state->motion);
        if (state->motion)
            break;
        state->action = func_080DBA5C(state->action);
        if (!state->action)
            request->phase = 2;
        break;
    }
    return 0;
}
