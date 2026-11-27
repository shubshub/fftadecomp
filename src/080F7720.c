#include "ffta.h"
#include "control_flags.h"

// Target 0x080F7720..0x080F7A34 (788 bytes): phase handler for a
// dialog-driven effect sequence.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *resource;
    u8 unknown_08[12];
    s16 kind;
    u16 mode;
} Event080F7720;

typedef struct {
    s16 x;
    s16 y;
} Offset080F7720;

typedef struct {
    u8 alternate;
    u8 mode;
    s16 x;
    s16 y;
    u8 ready;
    u8 finished;
    void *resource;
    void *object;
    void *position;
    void *loading;
    u32 outputs[2];
    void *coordinates;
    void *transition;
    void *layers[2];
    void *glow;
    void *display;
    void *dialog;
    void *overlay;
} State080F7720;

extern const u8 data_0839BC28[];
extern const u8 data_0839BC64[];
extern const u8 data_0839BC94[];
extern const u8 data_0839BCA8[];
extern const u8 data_0839BCB0[];
extern const u8 data_0839BCB8[];
extern const u8 data_088F58E0[];
extern const u8 data_089484DC[];
extern const u8 data_0894A028[];
extern const u8 data_0894A050[];
extern const u8 data_0894D69C[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(u8);
extern void func_080DE3BC(void *, u8);
extern void *func_080DD4B4(void *, u8);
extern void func_080DC0BC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                          void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void func_080DBA50(void *);
extern u8 func_080DE1F0(void *);
extern void *func_080D6134(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);

u32 func_080F7720(void *task, Event080F7720 *event, State080F7720 *state)
{
    switch (event->phase) {
    case 0:
    {
        u8 flags;

        state->alternate = 0;
        if (event->kind == 0x83)
            state->alternate = 1;
        state->mode = event->mode;
        state->resource = event->resource;
        flags = 5;
        if (state->mode)
            flags = 0;
        state->loading = func_080E03F8(state->resource, data_0839BC28, flags,
                                       7, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->loading = func_080E05DC(state->loading);
        if (state->loading == 0) {
            if (func_080D3B54(state->resource)) {
                event->phase = 2;
            } else {
                u16 style = 0x34;

                if (state->alternate == 1)
                    style = 0x8007;
                state->dialog = func_080DDF68(state->resource, &state->object,
                                              style, 2, &state->ready,
                                              data_0839BCA8, 3, 0, task);
                func_080DBDC8(state->object, &state->x, &state->y);
                event->phase++;
            }
        }
        break;
    case 0x101:
    {
        Offset080F7720 offsets[4] = {
            {4, -2}, {4, -2}, {-4, -2}, {-4, -2}
        };

        if (state->ready) {
            s8 facing = func_080DBC88(state->object);

            func_080D7220(data_088F58E0, 0, 2,
                          state->x + offsets[facing].x,
                          state->y + offsets[facing].y, 0);
            state->transition = func_080D3E9C(data_0894D69C, task);
            state->layers[0] = func_080D4704(data_0894A028, task);
            state->layers[1] = func_080D4704(data_0894A050, task);
            state->overlay = func_080DFD8C(data_0839BCB0, 1, 4, 0, task);
            event->phase++;
        }
        break;
    }
    case 0x102:
        if (func_080D48DC(state->layers, 2)) {
            state->transition = func_080D3F08(state->transition);
            if (state->transition == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(2);
                func_080DE3BC(state->object, 0);
                event->phase++;
            }
        }
        break;
    case 0x103:
        if (state->finished) {
            func_080DC0BC(func_080DD4B4(state->resource, 0), 0);
            event->phase++;
        }
        break;
    case 0x104:
        if (func_080D8B4C() == 0) {
            void *member;
            s16 x;
            s16 y;

            if (func_080D8858(state->resource, 0) == 0) {
                event->phase = 0x105;
                break;
            }
            member = func_080DD4A4(state->resource, 0);
            state->position = func_080DD748(member, &x, &y, 0);
            state->coordinates = func_080D6098(x, y, 0, 1, 2, state->outputs,
                                               data_0839BC64, task);
            state->glow = func_080D4704(data_089484DC, task);
            state->display = func_080DCFE4(member, data_0839BC94, 12, 20, 2,
                                           task, 20);
            state->overlay = func_080DFD8C(data_0839BCB8, 1, 4, 0, task);
            func_080DBA50(state->dialog);
            state->dialog = 0;
            event->phase++;
        }
        break;
    case 0x105:
        if (func_080DE1F0(state->object)) {
            state->coordinates = func_080D6134(state->coordinates);
            if (state->coordinates == 0) {
                state->glow = func_080D4774(state->glow);
                if (state->glow == 0) {
                    state->display = func_080DBA5C(state->display);
                    if (state->display == 0)
                        event->phase = 2;
                }
            }
        }
        break;
    }
    return 0;
}
