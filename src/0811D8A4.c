#include "ffta.h"
#include "control_flags.h"

/* 0x0811D8A4..0x0811DA64. Registered by 0811DA64 with a 0x4c-byte payload. */
typedef struct {
    u8 unknown_00[8];
    s16 x, y, z;
} PositionState;

typedef struct {
    u8 unknown_00[2];
    u8 x, y;
} Position;

typedef struct {
    u16 tick;
    u8 channels[2];
    u16 commands[2];
} SequenceEvent;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    void **effect;
    u8 unknown_0C[16];
} Descriptor;

typedef struct {
    u16 unknown_00;
    s16 x, y;
    u16 unknown_06;
    PositionState *object;
    void **effect;
    void *first_task;
    void *first_output;
    void *second_task;
    void *second_output;
    void *third_task;
    void *third_outputs[7];
    void *sequence;
    void *extra_task;
    void *event;
} Payload;

extern const Position data_088F53DC;
extern const u8 data_0894DDBC[];
extern const u8 data_083A6FD4[];
extern const u8 data_083A6FEC[];
extern const u8 data_083A7004[];
extern u8 data_0894AC90[];
extern const SequenceEvent data_083A70BC[], data_083A70C4[];

extern void func_080DBDC8(const PositionState *, s16 *, s16 *);
extern void func_080D7220(const Position *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080DFD8C(const SequenceEvent *, u8, u16, u16, void *);
extern int func_080DFAD0(int);
extern void *func_080D6134(void *);
extern void func_080DFAEC(void *);
extern void *func_080D4704(void *, void *);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(u8);
extern void func_080D4020(void);
extern void *func_080DBA5C(void *);
extern void *func_080D4774(void *);

u32 func_0811D8A4(void *task, Descriptor *descriptor, void *payload)
{
    Payload *state = payload;

    switch (descriptor->phase) {
    case 0:
        state->object = descriptor->value;
        state->effect = descriptor->effect;
        func_080DBDC8(state->object, &state->x, &state->y);
        break;
    case 1:
        break;
    case 0x100:
        func_080D7220(&data_088F53DC, 0, 2, state->x, (s16)(state->y - 24), 0);
        state->sequence = func_080D3E9C(data_0894DDBC, task);
        state->first_task = func_080D6098(state->x, (s16)(state->y - 36), 0, 1,
            1, &state->first_output, data_083A6FD4, task);
        state->event = func_080DFD8C(data_083A70BC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (!(u8)func_080DFAD0((int)*state->effect))
            break;
        state->first_task = func_080D6134(state->first_task);
        if (state->first_task)
            break;
        func_080DFAEC(*state->effect);
        state->second_task = func_080D6098(state->x, (s16)(state->y - 24), 0, 1,
            1, &state->second_output, data_083A6FEC, task);
        state->extra_task = func_080D4704(data_0894AC90, task);
        state->event = func_080DFD8C(data_083A70C4, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        state->second_task = func_080D6134(state->second_task);
        if (state->second_task)
            break;
        state->third_task = func_080D6098(state->x, (s16)(state->y - 24), 0, 1,
            7, state->third_outputs, data_083A7004, task);
        descriptor->phase++;
        break;
    case 0x103:
        state->sequence = func_080D3F08(state->sequence);
        if (state->sequence)
            break;
        state->third_task = func_080D6134(state->third_task);
        if (state->third_task)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080D4020();
        *state->effect = func_080DBA5C(*state->effect);
        if (*state->effect)
            break;
        state->extra_task = func_080D4774(state->extra_task);
        if (!state->extra_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
