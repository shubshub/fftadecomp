/* 0x080F378C: complete 310-byte owner. */
#include "ffta.h"
#include "effect_task.h"

typedef struct TargetGroup TargetGroup;
typedef struct ChildObject ChildObject;
typedef struct PositionState PositionState;

typedef struct {
    u16 phase;
    u16 unknown_02;
    TargetGroup *target;
} ActionRecord;

typedef struct {
    u16 countdown;
    u8 ready;
    u8 unknown_03;
    u8 effect_ready;
    u8 unknown_05[3];
    void *effect;
    ChildObject *selected;
    TargetGroup *target;
    void *request;
    void *animation;
    void *overlay;
} ActionState;

extern const u8 data_0839ACF8[];
extern const u8 data_0839ACB8[];
extern const u8 data_0839AD08[];
extern const u8 data_0839ACE4[];
extern void *func_080DDF68(TargetGroup *, ChildObject **, u16, u8,
                          u8 *, const u8 *, u16, u16, void *);
extern ChildObject *func_080DD4A4(TargetGroup *, u8);
extern const PositionState *func_080DD4C4(const ChildObject *);
extern void func_080DBDC8(const PositionState *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, u8 *, const u8 *, void *);
extern void *func_080DFD8C(const u8 *, u8, u16, u16, void *);

extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);
extern u8 func_080DE244(ChildObject *);

u32 func_080F378C(void *context, ActionRecord *record, ActionState *state)
{
    s16 x;
    s16 y;
    ChildObject *child;

    switch (record->phase) {
    case 0:
        state->target = record->target;
        state->countdown = 0x47;
        break;
    case 0x100:
        if (--state->countdown == 0) {
            state->request = func_080DDF68(state->target, &state->selected,
                                          0x8007, 2, &state->ready,
                                          data_0839ACF8, 5, 0, context);
            record->phase++;
        }
        break;
    case 0x101:
        if (state->ready) {
            child = func_080DD4A4(state->target, 0);
            func_080DBDC8(func_080DD4C4(child), &x, &y);
            state->effect = func_080D6098(x, y, 0, 1, 1, &state->effect_ready,
                                         data_0839ACB8, context);
            state->overlay = func_080DFD8C(data_0839AD08, 1, 4, 10, context);
            state->animation = func_080DCFE4(child, data_0839ACE4, 12, 31,
                                            2, context, 31);
            record->phase++;
        }
        break;
    case 0x102:
        state->effect = func_080D6134(state->effect);
        if (!state->effect) {
            state->animation = func_080DBA5C(state->animation);
            if (!state->animation && func_080DE244(state->selected))
                record->phase = 2;
        }
        break;
    }
    return 0;
}
