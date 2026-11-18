#include "ffta.h"
#include "effect_task.h"

// Complete target: [0x080EF970, 0x080EFAAE), 318 bytes.

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
} Event080EF970;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    void *entity;
    void *outputs[3];
    void *task18;
    void *task1C;
    void *task20;
    void *task24;
} State080EF970;

typedef struct {
    u8 unknown_00[20];
} Record080EF970;

typedef struct {
    u32 value;
} Record080DD4C4;

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
} State080DD580;

typedef struct {
    u8 unknown_00[0x14];
    u8 bits[32];
} PackedBits080DD670;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
} PositionState;

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

extern const u16 data_08149D0C[2];
extern const u8 data_08399ABC[72];
extern const SequenceEvent data_08399B34[1];
extern const Record080EF970 data_08399B04[2];
extern void *func_081443FC(void *, const void *, u32);
extern u32 func_080DD4C4(const Record080DD4C4 *);
extern u8 func_080DD580(const State080DD580 *);
extern u8 func_080DD670(const PackedBits080DD670 *, u8);
extern void func_080DBDC8(const PositionState *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080DFD8C(const SequenceEvent *, u8, u16, u16, void *);
extern void *func_080DF8E8(void *, u8, u32, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

static inline int initialize_effect_state(State080EF970 *state, const Event080EF970 *event)
{
    int mode;

    state->object = event->object;
    state->entity = (void *)func_080DD4C4(state->object);
    state->entity = (void *)func_080DD4C4(state->object);
    mode = 2;
    if (func_080DD580(state->object)) {
        if (func_080DD670(state->object, 0))
            mode = 0;
        else
            mode = 1;
    }
    return mode;
}

u32 func_080EF970(void *context, void *request, void *payload)
{
    Event080EF970 *event = request;

    switch (event->state) {
    case 0: {
        State080EF970 *state;
        u16 values[2];
        int mode;
        u32 index;

        func_081443FC(values, data_08149D0C, 4);
        mode = initialize_effect_state(payload, event);
        state = payload;
        if (mode == 1) {
            s16 x, y;

            func_080DBDC8(state->entity, &x, &y);
            state->task18 = func_080D6098(x, y, 0, 1, 3, state->outputs,
                                          data_08399ABC, context);
            state->task24 = func_080DFD8C(data_08399B34, 1, 4, 180, context);
        }
        index = mode;
        if (mode == 2)
            index = 0;
        state->task20 = func_080DCFE4(state->object, &data_08399B04[index],
                                      12, values[index], 4, context, 216);
        if (mode == 0)
            state->task1C = func_080DF8E8(state->entity, 2, 224, context);
        state->state = 224;
        break;
    }
    case 1:
        break;
    case 0x100: {
        State080EF970 *state = payload;

        state->task18 = func_080D6134(state->task18);
        if (state->task18 != 0)
            break;
        state->task1C = func_080DBA5C(state->task1C);
        if (state->task1C != 0)
            break;
        state->task20 = func_080DBA5C(state->task20);
        if (state->task20 == 0)
            event->state = 2;
        break;
    }
    }
    return 0;
}
