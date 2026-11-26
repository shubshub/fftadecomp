#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Event;
typedef struct {
    u8 variant;
    u8 unknown_01;
    u16 timer;
    u8 effect_index;
    u8 mode;
    u8 direction;
    u8 unknown_07;
    s16 x;
    s16 y;
    u8 signal;
    u8 unknown_0d;
    u16 graphic;
    void *sprite;
    u8 coordinate_output[8];
    void *coordinate_task;
    void *layer_task;
    void *actor;
    void *unit;
    void *position;
    void *target;
    void *initial_task;
    void *actor_task;
    void *setup_task;
    void *record_task;
} State;
typedef struct {
    const void *entries[4];
} DirectionTable;

extern u8 data_06017A60[];
extern const DirectionTable data_08149F04;
extern const u8 data_083A1D64[];
extern const u8 data_083A1E1C[];
extern const u8 data_083A1E20[];
extern const u8 data_0894A76C[];
extern const u8 data_083A1E28[];
extern const u8 data_083A1DC4[];
extern const u8 data_083A1DF4[][20];
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern s16 func_080DD56C(void *);
extern void *func_080DDF68(void *, void **, u32, u32, u8 *, const void *, u32, u32, void *);
extern u32 func_080DD73C(const void *);
extern void *func_080D6098(s16, s16, s16, u8, u16, void *, const void *, void *);
extern void func_080D6194(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(void *);
extern void *func_080D6134(void *);
extern void *func_080D5FD8(u16, u8, s16, s16, u16, u32, u8, void *);
extern void func_080111A8(void *, u8);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D4774(void *);
extern void func_08011428(void *);
extern void *func_080DCFE4(void *, const void *, u16, u16, u16, void *, u16);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_0810ADF4(void *owner, Event *event, State *state)
{
    switch (event->phase) {
    case 0: {
        u8 animation;
        state->variant = event->variant;
        state->actor = event->actor;
        animation = 4;
        if (state->variant)
            animation = 0;
        if (event->flags & 2)
            state->mode = 1;
        state->initial_task = func_080E03F8(state->actor, data_083A1D64, animation, 0, 0, owner);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->initial_task = func_080E05DC(state->initial_task);
        if (state->initial_task)
            break;
        if (func_080D3B54(state->actor)) {
            event->phase = 2;
            break;
        }
        state->unit = func_080DD47C(state->actor);
        state->target = func_080DD4A4(state->actor, 0);
        state->position = func_080DD748(state->target, &state->x, &state->y, 0);
        state->direction = func_080DBC88(state->unit);
        state->graphic = func_080DD56C(state->target);
        state->setup_task = func_080DDF68(state->actor, 0, 92, 1, &state->signal,
                                         data_083A1E1C, 0, 0, owner);
        event->phase++;
        break;
    case 0x101: {
        DirectionTable directions = data_08149F04;
        s16 y_offset;
        if (!state->signal)
            break;
        y_offset = 0;
        if ((u8)func_080DD73C(state->position))
            y_offset = -8;
        state->coordinate_task = func_080D6098(state->x, (s16)(state->y + y_offset), 0, 1, 1,
            state->coordinate_output, directions.entries[state->direction], owner);
        if (state->direction > 1)
            func_080D6194(state->coordinate_task, 1);
        state->record_task = func_080DFD8C(data_083A1E20, 1, 4, 0, owner);
        state->effect_index = 0;
        if (!state->graphic)
            state->effect_index = 1;
        if (!func_080DD580(state->target) || state->effect_index)
            event->phase = 0x105;
        else
            event->phase++;
        break;
    }
    case 0x102:
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task)
            break;
        state->sprite = func_080D5FD8(state->graphic, 0, state->x, (s16)(state->y - 32),
                                     0, (u32)data_06017A60, 8, owner);
        func_080111A8(state->sprite, 1);
        state->timer = 6;
        event->phase++;
        break;
    case 0x103:
        if (--state->timer)
            break;
        func_080111A8(state->sprite, 0);
        state->layer_task = func_080D4724(data_0894A76C, owner, 20);
        state->record_task = func_080DFD8C(data_083A1E28, 1, 4, 0, owner);
        event->phase++;
        break;
    case 0x104:
        state->layer_task = func_080D4774(state->layer_task);
        if (state->layer_task)
            break;
        func_08011428(state->sprite);
        state->sprite = 0;
        state->coordinate_task = func_080D6098(state->x, state->y, 0, 1, 2,
                                         state->coordinate_output, data_083A1DC4, owner);
        event->phase++;
        break;
    case 0x105:
        state->coordinate_task = func_080D6134(state->coordinate_task);
        if (state->coordinate_task)
            break;
        state->actor_task = func_080DCFE4(state->target, data_083A1DF4[state->effect_index],
                                         12, 0, 12, owner, 0);
        event->phase++;
        break;
    case 0x106:
        if (!func_080DE244(state->unit))
            break;
        state->actor_task = func_080DBA5C(state->actor_task);
        if (!state->actor_task)
            event->phase = 2;
        break;
    }
    return 0;
}
