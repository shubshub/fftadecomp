#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown02;
    void *primary;
    u8 unknown08[12];
    u16 flags;
    u16 variant;
} Event080F7A34;

typedef struct {
    u8 flags;
    u8 variant;
    s16 x;
    s16 y;
    u16 unknown06;
    void *source;
    void *position;
    void *outputs[2];
    void *coordinates;
    void *display;
    void *effect;
} State080F7A34;

extern const u8 data_0839BD44[];
extern const u8 data_0839BD8C[];
extern const u8 data_0839BDCC[];
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16,
                          void **, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16,
                          u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DBA5C(void *);

u32 func_080F7A34(void *task, Event080F7A34 *event, State080F7A34 *state)
{
    switch (event->phase) {
    case 0:
        state->flags = event->flags;
        state->variant = event->variant;
        state->source = event->primary;
        state->position = func_080DD748(state->source, &state->x, &state->y, 0);
        break;
    case 1:
        break;
    case 0x100:
    {
        u16 direction;
        u16 effect_flags;

        state->coordinates = func_080D6098(state->x, state->y, 0, 1, 2,
                                          state->outputs, data_0839BD44, task);
        direction = (state->flags & 1) ? 4 : 2;
        state->display = func_080DCFE4(state->source,
                                      data_0839BD8C + state->variant * 20,
                                      12, 20, direction, task, 20);
        effect_flags = (state->flags & 1) ? 16 : 8;
        state->effect = func_080DFD8C(data_0839BDCC, 1,
                                     effect_flags | 4, 0, task);
        ++event->phase;
        break;
    }
    case 0x101:
        state->display = func_080DBA5C(state->display);
        if (!state->display)
            event->phase = 2;
        break;
    }
    return 0;
}
